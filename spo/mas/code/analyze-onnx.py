# Python Standard Library
from argparse import ArgumentParser
import logging
from pathlib import Path

# External Library
import onnx
from onnx import shape_inference
from onnx import numpy_helper

# Internal Modules
from mas.core import LayerOutput, ValueID
from mas.core import MASElem, MASModel, MASRunner
from mas.aux import create_driver_logger

# Logger
logger = create_driver_logger()

# Check onnx version
#
# 1.9.0 Release Date: Apr 20, 2021
#
# See https://pypi.org/project/onnx/#history
assert onnx.__version__ == '1.9.0'

###
### ONNX Import Errors
###

class HasDimParam(Exception):
  pass
# class HasDimParam

class HasUnsupportedAttrType(Exception):
  def __init__(self, tname):
    self._tname = tname

  @property
  def tname(self):
    return self._tname
# class HasUnsupportedAttrType

###
### ONNX Proto Wrappers
###

# ONNX TensorProto.DataType
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L462-L491
class ONNXTensorDataType:
  avgbit = {
    'FLOAT': 32,

    'UINT8': 8,
    'INT8': 8,

    'UINT16': 16,
    'INT16': 16,

    'UINT32': 32,
    'INT32': 32,

    'UINT64': 64,
    'INT64': 64,
  }

  def __init__(self, value):
    self._value = value
  # def __init__: END

  def to_mas_elem(self):
    name = onnx.onnx_ml_pb2.TensorProto.DataType.Name(self._value)
    avgbit = self.avgbit[name]
    return MASElem(name, avgbit)
  # def to_mas_elem: END
# class ONNXTensorDataType: END


# ONNX TensorShapeProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L625-L642
class ONNXTensorShape:
  def __init__(self, value):
    self._value = value
  # def __init__

  # EXCEPTION
  #
  # HasDimParam
  # > There is a unknown dimension
  def to_mas_dims(self) -> list:
    def dim_value_of(d) -> int:
      if d.WhichOneof('value') != 'dim_value':
        # NOTE dim_param is NOT supported
        raise HasDimParam
      # if: END

      return int(d.dim_value)
    # def dim_value_of: END
    return [ dim_value_of(d) for d in self._value.dim ]
  # def to_mas_dims: END
# class ONNXTensorShape: END


# ONNX TypeProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L644-L697
class ONNXType:
  def __init__(self, value):
    self._value = value
  # def __init__: END

  # SIGNATURE
  #
  # () -> (MAS.ElemDetail, Dims)
  def to_mas_elem_and_dims(self):
    # FIX CALLER UNLESS
    if self._value.WhichOneof('value') != 'tensor_type':
      print(self._value.WhichOneof('value'))
      exit(1)

    onnx_tensor_type = self._value.tensor_type

    mas_elem = ONNXTensorDataType(onnx_tensor_type.elem_type).to_mas_elem()
    mas_dims = ONNXTensorShape(onnx_tensor_type.shape).to_mas_dims()

    return mas_elem, mas_dims
  # def to_mas_elem_and_dims: END
# class ONNXType: END


# ONNX TensorProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L458-L599
class ONNXTensor:
  def __init__(self, value):
    self._value = value

  # Signature
  #
  # () -> (MAS.ElemDetail, Dims)
  def to_mas_elem_and_dims(self):
    mas_elem = ONNXTensorDataType(self._value.data_type).to_mas_elem()
    mas_dims = self._value.dims
    return mas_elem, mas_dims
  # def to_elem_and_dims: END
# class ONNXTensor: END


# ONNX ValueInfoProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L172-L182
class ONNXValueInfo:
  def __init__(self, value):
    # name and type MUST be present
    # See https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L172-L182
    assert value.HasField('name')
    assert value.HasField('type')
    self._value = value
  # def __init__: END

  @property
  def name(self):
    return self._value.name

  def to_mas_elem_and_dims(self):
    return ONNXType(self._value.type).to_mas_elem_and_dims()
# class ONNXValueInfo: END


# ONNX AttributeProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L107-L170
class ONNXAttribute:
  # Describe how to get a value (of a given type) from AttributeProto object
  converter_registry = {
    'INT': lambda o: o.i,
    'INTS': lambda o: o.ints,

    'FLOAT': lambda o: o.f,
    'FLOATS': lambda o: o.floats,

    'STRING': lambda o: o.s,
    'STRINGS': lambda o: o.strings,

    # See https://github.com/onnx/onnx/blob/rel-1.9.0/docs/PythonAPIOverview.md#manipulating-tensorproto-and-numpy-array
    'TENSOR': lambda o: numpy_helper.to_array(o.t),
  }

  def __init__(self, value):
    # https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L134
    # > The name field MUST be present for this version of the IR.
    assert value.HasField('name')
    self._value = value
  # def __init__: END

  @property
  def name(self):
    return self._value.name

  @property
  def value(self):
    attr_typename = onnx.onnx_ml_pb2.AttributeProto.AttributeType.Name(self._value.type)
    if attr_typename not in self.converter_registry:
      raise HasUnsupportedAttrType(attr_typename)
    # if: END
    attr_convert = self.converter_registry[attr_typename]
    return attr_convert(self._value)
  # def to_value: END
# class ONNXAttribute: END


# ONNX OperatorSetIDProto
#
# DEFINITION
#
# https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L699-L712
class ONNXOperatorSetId:
  def __init__(self, value):
    # 'version' MUST be present
    # See https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L710
    assert value.HasField('version')

    self._value = value
  # def __init__: END

  @property
  def name(self):
    setid = self._value

    # > The empty string ("") or absence of this field implies the operator
    # > set that is defined as part of the ONNX specification.
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L704-L705
    if (not setid.HasField('domain')) or setid.domain == '':
      return f'onnx.v{setid.version}'
    # if: END

    return f'{setid.domain}.v{setid.version}'
  # def name: END
# class ONNXOperatorSetId: END


def read_from(onnx_path):
  # See https://github.com/onnx/onnx/blob/rel-1.9.0/docs/PythonAPIOverview.md
  onnx_model = shape_inference.infer_shapes(onnx.load(onnx_path))

  # ONNX Standard Opset Version
  onnx_version = None
  # Custom (non-standard) Opset Versions
  #
  # Type: Map (opset name (string) -> opset version (int))
  custom_opset_registry = { }

  for onnx_opset in onnx_model.opset_import:
    # > The version of the operator set being identified.
    # > This field MUST be present in this version of the IR.
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L709-L710
    assert onnx_opset.HasField('version')

    # > The domain of the operator set being identified.
    # > The empty string ("") or absence of this field implies the operator
    # > set that is defined as part of the ONNX specification.
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L703-L707
    if (not onnx_opset.HasField('domain')) or (onnx_opset.domain == ''):
      # CONJECTURE: There is exactly ONE opset with empty (or missing) domain
      assert onnx_version is None
      onnx_version = onnx_opset.version
    else:
      assert onnx_opset.HasField('domain')
      assert onnx_opset.domain not in custom_opset_registry
      custom_opset_registry[onnx_opset.domain] = onnx_opset.version
    # if: END
  # for onnx_opset: END

  # CASE: lacks of ONNX standard version
  assert onnx_version is not None

  # CASE: use custom opsets
  if len(custom_opset_registry) > 0:
    print(f'error: this model uses custom opsets')
    print()
    print('CUSTOM OPSET')
    for name, version in custom_opset_registry.items():
      print(f'- {name}:{version}')
    # for: END

    # DESIGN NOTE: WHY REJECT?
    #
    # Shape is essential for model characteristic analysis, but
    # infer_shapes may does not work in the presence of custom opsets.
    #
    # DESIGN NOTE: WHY HERE?
    #
    # Let's collect all custom opsets, and report all of them here in order to
    # improve user experience
    exit(1)
  # if: END

  # > The parameterized graph that is evaluated to execute the model.
  # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L374-L375
  onnx_graph = onnx_model.graph

  # str -> (MAS.ElemDetail, int list)
  onnx_symtbl = {}

  def add_value_to_symtbl(v):
    assert type(v) == ONNXValueInfo
    try:
      onnx_symtbl[v.name] = v.to_mas_elem_and_dims()
    except HasDimParam:
      print(f'error: there is a unresolved dimension parameter: {v.name}')
      exit(1)
    # try: END
  # def add_value_to_symtbl: END

  for onnx_input_value in [ ONNXValueInfo(v) for v in onnx_graph.input ]:
    add_value_to_symtbl(onnx_input_value)
  # for onnx_input_value: END

  for onnx_output_value in [ ONNXValueInfo(v) for v in onnx_graph.output ]:
    add_value_to_symtbl(onnx_output_value)
  # for onnx_output_value: END

  # Iterate 'onnx_graph.value_info'
  #
  # > Information for the values in the graph. The ValueInfoProto.name's must be distinct.
  # > It is optional for a value to appear in value_info list.
  # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L439-L441
  #
  # It is experimentally validated that shape_inference.infer_shapes fills this field.
  for onnx_value in [ ONNXValueInfo(v) for v in onnx_graph.value_info ]:
    add_value_to_symtbl(onnx_value)
  # for onnx_value: END

  for onnx_tensor in onnx_graph.initializer:
    # DESIGN NOTE: Is this assert safe?
    #
    # Note that 'name' is optional according to the definition of TensorProto:
    # > Optionally, a name for the tensor.
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L541
    #
    # However, TensorProto in Graph initializer MUST have a name.
    # > Each initializer (both TensorProto as well SparseTensorProto) MUST have a name. ...
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L424
    assert onnx_tensor.HasField('name')

    mas_elem, mas_dims = ONNXTensor(onnx_tensor).to_mas_elem_and_dims()

    # DESIGN NOTE: Why is this check required?
    #
    # onnx_graph.input and onnx_graph.initializer may be overlapped
    # > but the name MAY also appear in the input list.
    # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L426
    if onnx_tensor.name in onnx_symtbl:
      expected_elem, expected_dims = onnx_symtbl[onnx_tensor.name]
      assert mas_elem.tname() == expected_elem.tname()
      assert mas_dims == expected_dims
      continue
    # if: END

    onnx_symtbl[onnx_tensor.name] = (mas_elem, mas_dims)
  # for onnx_tensor: END

  # NOT SUPPORTED, YET
  #
  # TODO Support sparse initializer
  assert len(onnx_graph.sparse_initializer) == 0

  # A set of onnx const name
  onnx_consts = set()

  # Iterate 'initializer' and 'sparse_initializer' to find 'const' tensors
  #
  # From https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L423-L426
  # > A list of named tensor values, used to specify constant inputs of the graph.
  # > Each initializer (both TensorProto as well SparseTensorProto) MUST have a name.
  for onnx_tensor in list(onnx_graph.initializer) + list(onnx_graph.sparse_initializer):
    # onnx_tensor : TensorProto or SparseTensorProto
    assert onnx_tensor.HasField('name')
    assert onnx_tensor.name in onnx_symtbl
    onnx_consts.add(onnx_tensor.name)
  # for onnx_tensor: END

  # To connect ONNX and MAS world
  onnx_vname_to_mas_vid = { }

  mas_model = MASModel(opset=f'onnx.v{onnx_version}')

  # Configure model inputs
  for onnx_graph_input in onnx_graph.input:
    # onnx_graph_input is a ValueInfoProto message

    # name/type field MUST be present.
    # See https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L172-L182
    value_name = onnx_graph_input.name

    if value_name in onnx_consts:
      # Skip constants
      continue

    mas_elem, mas_dims = onnx_symtbl[value_name]
    onnx_vname_to_mas_vid[onnx_graph_input.name] = mas_model.append_input(elem=mas_elem, dims=mas_dims)
  # for onnx_graph_input: END

  # Configure model data
  for onnx_const_name in onnx_consts:
    mas_elem, mas_dims = onnx_symtbl[onnx_const_name]
    onnx_vname_to_mas_vid[onnx_const_name] = mas_model.append_data(name=onnx_const_name, elem=mas_elem, dims=mas_dims)
  # for onnx_const_name: END

  # Configure model layers
  #
  # CONJECTURE: onnx.nodes are topologically sorted
  for onnx_node in onnx_graph.node:
    # onnx_node: NodeProto
    #
    # https://github.com/onnx/onnx/blob/rel-1.9.0/onnx/onnx.proto#L184-L209
    onnx_op = None

    # Custom opset is NOT supported intentionally.
    assert (not onnx_node.HasField('domain')) or (onnx_node.domain == '')
    # Q. How to use ai.onnx.training or ai.onnx.ml operations?
    #
    # - https://github.com/onnx/onnx/blob/rel-1.9.0/docs/Operators.md#aionnxpreviewtraining
    # - https://github.com/onnx/onnx/blob/rel-1.9.0/docs/Operators-ml.md
    #
    # There is no working example, yet.
    onnx_op = f'ai.onnx.{onnx_node.op_type}'

    mas_layer = mas_model.append_layer()

    # Configure layer op
    mas_layer.op = onnx_op

    # Configure layer attributes
    for onnx_attr in [ ONNXAttribute(o) for o in onnx_node.attribute]:
      try:
        mas_layer.set_attr(onnx_attr.name, onnx_attr.value)
      except HasUnsupportedAttrType as e:
        print(f'error: unsupported attr type: {e.tname}: {onnx_node.name} (op: {onnx_op})')
        exit(1)
      # try: END
    # for onnx_attr: END

    # Configure layer inputs
    for onnx_vname in onnx_node.input:
      mas_vid = onnx_vname_to_mas_vid[onnx_vname]
      mas_layer.add_input(mas_vid)
    # for onnx_vname: END

    # Configure layer outputs
    for output_index, onnx_vname in enumerate(onnx_node.output):
      mas_vid = ValueID(LayerOutput, f'{mas_layer.ind}:{output_index}')

      mas_elem, mas_dims = onnx_symtbl[onnx_vname]
      mas_model.create_value(vid=mas_vid, elem=mas_elem, dims=mas_dims)

      mas_layer.add_output(mas_vid)
      onnx_vname_to_mas_vid[onnx_vname] = mas_vid
    # for output_index, onnx_vname: END
  # for onnx_node: END

  # Configure model outputs
  for onnx_value in [ ONNXValueInfo(o) for o in onnx_graph.output]:
    mas_vid = onnx_vname_to_mas_vid[onnx_value.name]
    mas_model.append_output(mas_vid)
  # for onnx_value: END

  return mas_model
# def read_from: END


# CLI
parser = ArgumentParser(description='Analyze .onnx model with .mas script')
parser.add_argument('-m', '--model-path', metavar='PATH', required=True, dest='MODEL_PATH')
parser.add_argument('-v', dest='LOG_LEVEL', action='store_const', const=logging.INFO)
parser.add_argument('-vv', dest='LOG_LEVEL', action='store_const', const=logging.DEBUG)

args, rest = parser.parse_known_args()

if args.LOG_LEVEL is not None:
  logger.setLevel(args.LOG_LEVEL)
# if args.LOG_LEVEL: END

logger.info(f'Load "{args.MODEL_PATH}"')

mas_model = read_from(args.MODEL_PATH)

runner = MASRunner(mas_model)

for script_path in rest:
  runner.run(script_path)
