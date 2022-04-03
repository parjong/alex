# Python Standard Library
from argparse import ArgumentParser
from logging import info
from pathlib import Path

# External Library
import tflite

# Internal Modules
from mas.core import LayerOutput, ValueID
from mas.core import MASElem, MASModel, MASRunner

# Global Initialization
options2name = { }

for var_name in vars(tflite.BuiltinOptions):
  if not var_name.endswith('Options'):
    continue

  var_value = getattr(tflite.BuiltinOptions, var_name)
  options2name[var_value] = var_name

# Python version affects this helper
def is_python_builtin_method(meth_name):
  python_builtin_methods = [
    '__class__',
    '__delattr__',
    '__dir__',
    '__doc__',
    '__eq__',
    '__format__',
    '__ge__',
    '__getattribute__',
    '__gt__',
    '__hash__',
    '__init__',
    '__init_subclass__',
    '__le__',
    '__lt__',
    '__module__',
    '__ne__',
    '__new__',
    '__reduce__',
    '__reduce_ex__',
    '__repr__',
    '__setattr__',
    '__sizeof__',
    '__slots__',
    '__str__',
    '__subclasshook__',
    # Q: Who creates this function?
    '_tab',
  ]

  return meth_name in python_builtin_methods
# end is_python_builtin_method

def is_attr_method(meth_name):
  if is_python_builtin_method(meth_name):
    return False

  # Depends on 'flatbuffers' version (tested with 2.0)
  if meth_name == 'Init':
    return False

  if meth_name.startswith('GetRootAs'):
    return False

  return True
# end is_attr_method

def get_attr_methods(o):
  attr_methods = [ ]

  for meth_name in dir(o):
    # Skip non-attribute methods
    if not is_attr_method(meth_name):
      continue
    attr_methods.append(meth_name)

  return attr_methods
# end get_attr_methods

def make_enum_registry(t):
  registry = { }

  for name in vars(t):
    if name.startswith('_'):
      continue
    value = getattr(t, name)
    registry[value] = name

  return registry
# end make_enum_registry

def make_convert_fn(t):
  def f(v):
    r = make_enum_registry(t)
    return r[v]
  return f

# tflite.ActivationFunctionType -> string
def convert_FusedActivationFunction(v):
  registry = make_enum_registry(tflite.ActivationFunctionType)
  return registry[v]

# tflite.Padding -> string
def convert_Padding(v):
  registry = make_enum_registry(tflite.Padding)
  return registry[v]

class EnumField:
  def __init__(self, name, t):
    self._name = name
    self._convert_fn = make_convert_fn(t)

  def methods(self):
    return [self._name]

  def update(self, options, layer):
    get = getattr(options, self._name)
    value = get()
    layer.set_attr(self._name, self._convert_fn(value))

# Numeric Scalar Field
class ScalarField:
  def __init__(self, name, convert_fn=None):
    self._name = name

    self._convert_fn = convert_fn if convert_fn is not None else lambda v: str(v)

  def methods(self):
    return [self._name]

  def update(self, options, layer):
    get = getattr(options, self._name)
    value = get()
    layer.set_attr(self._name, self._convert_fn(value))

# Numeric List Field
class ListField:
  def __init__(self, prefix):
    self._prefix = prefix

  def methods(self):
    return [self._prefix, self._prefix + 'AsNumpy', self._prefix + 'Length']

  def update(self, options, layer):
    get = getattr(options, self._prefix + 'AsNumpy')
    layer.set_attr(self._prefix, get())

# 'opschema' abstract TFLITE flatbuffer schema
#
# Compatible with the following .fbs specification:
# > https://github.com/jackwish/tflite/blob/v2.4.0/3rdparty/schema.fbs
#
assert tflite.__version__ == '2.4.0'

# Corresponds to 'Pool2DOptions' table
pool2d_table = [
  EnumField('Padding', tflite.Padding),
  ScalarField('StrideH'),
  ScalarField('StrideW'),
  ScalarField('FilterWidth'),
  ScalarField('FilterHeight'),
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
]

# Corresponds to 'ReducerOptions' table
reducer_table = [
  ScalarField('KeepDims')
]

# For readability
no_field = [ ]

opschema = { }

opschema['ADD'] = [
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
  ScalarField('PotScaleInt16'),
]
opschema['AVERAGE_POOL_2D'] = pool2d_table
opschema['CONCATENATION'] = [
  ScalarField('Axis'),
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
]
opschema['CONV_2D'] = [
  ScalarField('DilationHFactor'),
  ScalarField('DilationWFactor'),
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
  ScalarField('StrideH'),
  ScalarField('StrideW'),
  EnumField('Padding', tflite.Padding),
]
opschema['DEPTHWISE_CONV_2D'] = [
  ScalarField('DepthMultiplier'),
  ScalarField('DilationHFactor'),
  ScalarField('DilationWFactor'),
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
  ScalarField('StrideH'),
  ScalarField('StrideW'),
  EnumField('Padding', tflite.Padding),
]
opschema['FULLY_CONNECTED'] = [
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
  EnumField('WeightsFormat', tflite.FullyConnectedOptionsWeightsFormat),
  ScalarField('KeepNumDims'),
  ScalarField('AsymmetricQuantizeInputs'),
]
opschema['LEAKY_RELU'] = [
  ScalarField('Alpha'),
]
opschema['MAX_POOL_2D'] = pool2d_table
opschema['MEAN'] = reducer_table
opschema['MUL'] = [
  EnumField('FusedActivationFunction', tflite.ActivationFunctionType),
]
opschema['PAD'] = no_field
opschema['RESHAPE'] = [
  ListField('NewShape')
]
opschema['RESIZE_BILINEAR'] = [
  ScalarField('AlignCorners'),
  ScalarField('HalfPixelCenters'),
]
opschema['SOFTMAX'] = [
  ScalarField('Beta')
]
opschema['SQUEEZE'] = [
  ListField('SqueezeDims')
]
opschema['TRANSPOSE'] = no_field
opschema['TRANSPOSE_CONV'] = [
  EnumField('Padding', tflite.Padding),
  ScalarField('StrideH'),
  ScalarField('StrideW'),
]
# end opschema

# TFLite-to-MAS Converter
class TFL2MASConverter:
  def __init__(self):
    # Initialize 'TFL TensorType -> MAS MASElem'
    self._dtype = { }

    self._dtype[tflite.TensorType.UINT8] = MASElem('UINT8', 8)
    self._dtype[tflite.TensorType.FLOAT32] = MASElem('FLOAT32', 32)
    self._dtype[tflite.TensorType.INT32] = MASElem('INT32', 32)

  def get_elem_detail_of_tfl_dtype(self, tfl_dtype):
    try:
      return self._dtype[tfl_dtype]
    except:
      r = make_enum_registry(tflite.TensorType)
      print(f'error: not found: {r[tfl_dtype]}')
      raise

def read_from(tflite_path, graph_index=None):
  assert graph_index is not None

  # "TFL Tensor Index (per Graph) -> MAS Value ID" dict
  tidx2vid = { }
  tfl2mas = TFL2MASConverter()

  with open(tflite_path, 'rb') as f:
    tfl_content = f.read()

  tfl_model = tflite.Model.GetRootAsModel(tfl_content, 0)
  tfl_version = tfl_model.Version()

  # Buffer 0 denotes 'empty buffer'
  assert tfl_model.Buffers(0).DataLength() == 0 # FIX .tflite UNLESS

  assert graph_index < tfl_model.SubgraphsLength() # FIX CALLER UNLESS
  tfl_graph = tfl_model.Subgraphs(graph_index)

  mas_model = MASModel(opset=f'TFL{tfl_version}')

  # Configure model input
  for tensor_idx in tfl_graph.InputsAsNumpy():
    tfl_tensor = tfl_graph.Tensors(tensor_idx);
    tfl_tensor_dtype = tfl_tensor.Type()
    tfl_tensor_shape = tfl_tensor.ShapeAsNumpy()

    mas_elem_detail = tfl2mas.get_elem_detail_of_tfl_dtype(tfl_tensor_dtype)

    tidx2vid[tensor_idx] = mas_model.append_input(elem=mas_elem_detail, dims=tfl_tensor_shape)
  # Configure model input - Done

  # Configure model data
  for tensor_idx in range(0, tfl_graph.TensorsLength()):
    tfl_tensor = tfl_graph.Tensors(tensor_idx)
    tfl_buffer = tfl_model.Buffers(tfl_tensor.Buffer())

    # Ignore 'empty' buffer
    if tfl_buffer.DataLength() == 0:
      continue

    # Q: Is this safe?
    assert len(tfl_tensor.Name()) > 0

    tfl_tensor_name = tfl_tensor.Name().decode('utf-8')
    tfl_tensor_dtype = tfl_tensor.Type()
    tfl_tensor_shape = tfl_tensor.ShapeAsNumpy()

    mas_elem_detail = tfl2mas.get_elem_detail_of_tfl_dtype(tfl_tensor_dtype)
    tidx2vid[tensor_idx] = mas_model.append_data(name=tfl_tensor_name, elem=mas_elem_detail, dims=tfl_tensor_shape)
  # Configure model data - Done

  # Configure model layer
  for op_idx in range(0, tfl_graph.OperatorsLength()):
    tfl_operator = tfl_graph.Operators(op_idx)

    tfl_opcode_index = tfl_operator.OpcodeIndex()
    tfl_opcode = tfl_model.OperatorCodes(tfl_opcode_index).BuiltinCode()
    # CustomCode is not supported
    assert tfl_opcode is not None

    op = tflite.BUILTIN_OPCODE2NAME[tfl_opcode]

    layer = mas_model.append_layer()
    assert layer.ind == op_idx

    layer.op = op

    # Configure layer attribute
    tfl_options = tfl_operator.BuiltinOptions()
    tfl_options_type = tfl_operator.BuiltinOptionsType()

    # Some operation has no Options (e.g. Logistics)
    if tfl_options_type in options2name:
      tfl_option_name = options2name[tfl_options_type]

      tfl_casted_options_ctor = getattr(tflite, tfl_option_name)
      tfl_casted_options = tfl_casted_options_ctor()
      tfl_casted_options.Init(tfl_options.Bytes, tfl_options.Pos)

      # Collect attribute methods to inspect
      attr_methods = get_attr_methods(tfl_casted_options)

      if op not in opschema:
        raise Exception(f'Unknown Op: {op}')

      for fld in opschema[op]:
        # Remove covered attr methods
        for meth_name in fld.methods():
          attr_methods.remove(meth_name)
        # Update layer
        fld.update(tfl_casted_options, layer)

      # Check coverage
      if len(attr_methods) > 0:
        print(f'Unknown fields from {op}')
        for attr_meth in attr_methods:
          print(f'  {attr_meth}')
        raise Exception('Unknown field')
    # Configure layer attribute - Done

    # Configure layer input
    for input_idx in range(0, tfl_operator.InputsLength()):
      tfl_tensor_idx = tfl_operator.Inputs(input_idx)
      mas_value_id = tidx2vid[tfl_tensor_idx]
      layer.add_input(mas_value_id)
    # Configure layer input - Done

    # Configure layer output
    for output_idx in range(0, tfl_operator.OutputsLength()):
      output_value_id = ValueID(LayerOutput, f'{layer.ind}:{output_idx}')

      tfl_tensor_idx = tfl_operator.Outputs(output_idx)
      tfl_tensor = tfl_graph.Tensors(tfl_tensor_idx)
      tfl_tensor_dtype = tfl_tensor.Type()
      tfl_tensor_shape = tfl_tensor.ShapeAsNumpy()

      # Create 'output' value
      mas_elem_detail = tfl2mas.get_elem_detail_of_tfl_dtype(tfl_tensor_dtype)
      mas_value_detail = mas_model.create_value(vid=output_value_id, elem=mas_elem_detail, dims=tfl_tensor_shape)

      # Update 'layer' output
      layer.add_output(output_value_id)
      tidx2vid[tfl_tensor_idx] = output_value_id
    # Configure layer output - Done
  # Configure model layer - Done

  # Configure model output
  for tensor_idx in tfl_graph.OutputsAsNumpy():
    tfl_tensor = tfl_graph.Tensors(tensor_idx);
    mas_model.append_output(tidx2vid[tensor_idx])
  # Configure model output - Done

  return mas_model

# CLI
parser = ArgumentParser(description='Analyze .tflite model with .mas scrikpts')
parser.add_argument('-m', '--model-path', metavar='PATH', required=True, dest='MODEL_PATH')

args, rest = parser.parse_known_args()

info(f'Load .tflite from {args.MODEL_PATH}')

# TODO Permit Graph Selection
mas_model = read_from(args.MODEL_PATH, graph_index=0)

runner = MASRunner(mas_model)

for script_path in rest:
  runner.run(script_path)
