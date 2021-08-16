import rfl.core as core

import tflite

class DataType:
  def __init__(self, value):
    self._value = value

  @property
  def bitwidth(self):
    table = {
      tflite.TensorType.INT8: 8,
      tflite.TensorType.UINT8: 8,
      tflite.TensorType.INT16: 16,
      tflite.TensorType.INT32: 32,
      tflite.TensorType.INT64: 64,
      tflite.TensorType.FLOAT32: 32,
      tflite.TensorType.FLOAT64: 64,
    }
    return table[self._value]

class Operator:
  def __init__(self, operator, parent=None):
    self._operator = operator
    self._parent = parent # Graph

  @property
  def raw(self):
    return self._operator

  @property
  def graph(self):
    return self.parent

  @property
  def model(self):
    return self.graph.model

  @property
  def parent(self):
    return self._parent


class Graph:
  def __init__(self, graph, parent=None):
    self._graph = graph

    # assert type(parent) is Model
    self._parent = parent # Model

  @property
  def raw(self):
    return self._graph

  @property
  def parent(self):
    return self._parent

  @property
  def model(self):
    return self.parent

  def operator(self, n):
    return Operator(self.raw.Operators(n), parent=self)


class Model:
  def __init__(self, model):
    self._model = model

  @property
  def raw(self):
    return self._model

  def graph(self, n):
    raw_graph = self.raw.Subgraphs(0)
    return Graph(raw_graph, parent=self)

  def from_file_at(path):
    with open(path, 'rb') as f:
      content = f.read()

    return Model(tflite.Model.GetRootAsModel(content, 0))


class OperatorAbstractionContext(object):
  """Operation Cost Modeling Context"""
  def __init__(self, operator: Operator):
    self._operator = operator

  @property
  def operator(self):
    return self._operator

  @property
  def graph(self):
    return self.operator.graph

  @property
  def model(self):
    return self.operator.model

  def get_tensor_index_of_input_(self, n):
    return self.operator.raw.Inputs(n)

  def get_tensor_index_of_output_(self, n):
    return self.operator.raw.Outputs(n)

  def get_shape_of_tensor_index_(self, tensor_idx):
    return self.graph.raw.Tensors(tensor_idx).ShapeAsNumpy()


class OperatorAbstraction:
  def __init__(self, kind, attr={}, weights=[]):
    self.kind = kind
    self.attr = attr
    self.weights = weights


### Operator Abstraction Helpers
def conv2d(ctx: OperatorAbstractionContext):
  operator = ctx.operator.raw
  graph = ctx.graph.raw

  assert operator.BuiltinOptionsType() == tflite.BuiltinOptions.Conv2DOptions
  option = operator.BuiltinOptions()
  conv2d_option = tflite.Conv2DOptions()
  conv2d_option.Init(option.Bytes, option.Pos)

  ifm_idx = ctx.get_tensor_index_of_input_(0)
  ker_idx = ctx.get_tensor_index_of_input_(1)
  has_bias = (operator.InputsLength() > 2)

  assert operator.OutputsLength() == 1
  ofm_idx = operator.Outputs(0)

  assert conv2d_option.DilationHFactor() == 1
  assert conv2d_option.DilationWFactor() == 1

  # ASSUME: NHWC
  _, _, _, IFM_C = ctx.get_shape_of_tensor_index_(ifm_idx)

  # ASSUME: OHWI
  ker_dtype = DataType(graph.Tensors(ker_idx).Type())
  ker_shape = ctx.get_shape_of_tensor_index_(ker_idx)
  KER_O, KER_H, KER_W, KER_I = ker_shape
  assert IFM_C == KER_I

  # ASSUME: NHWC
  OFM_N, OFM_H, OFM_W, OFM_C = ctx.get_shape_of_tensor_index_(ofm_idx)
  assert OFM_C == KER_O

  # bitwidth
  return OperatorAbstraction(core.Operation.Conv2D,
    attr={
      "OFM_N": OFM_N,
      "OFM_H": OFM_H,
      "OFM_W": OFM_W,
      "OFM_C": OFM_C,
      "KER_H": KER_H,
      "KER_W": KER_W,
      "KER_I": KER_I,
      "WITH_BIAS": has_bias,
    },
    weights=[core.Tensor(shape=list(ker_shape), bitwidth=ker_dtype.bitwidth)],
  )

def dconv2d(ctx: OperatorAbstractionContext):
  operator = ctx.operator.raw
  graph = ctx.graph.raw

  assert operator.BuiltinOptionsType() == tflite.BuiltinOptions.DepthwiseConv2DOptions
  option = operator.BuiltinOptions()
  dconv2d_option = tflite.DepthwiseConv2DOptions()
  dconv2d_option.Init(option.Bytes, option.Pos)

  ifm_idx = ctx.get_tensor_index_of_input_(0)
  ker_idx = ctx.get_tensor_index_of_input_(1)
  has_bias = (operator.InputsLength() > 2)

  assert operator.OutputsLength() == 1
  ofm_idx = operator.Outputs(0)

  assert dconv2d_option.DilationHFactor() == 1
  assert dconv2d_option.DilationWFactor() == 1

  # ASSUME: NHWC
  _, _, _, IFM_C = ctx.get_shape_of_tensor_index_(ifm_idx)

  # ASSUME: 1 x H x W x (DEPTH MULTIPLIER * IFM_C)
  ker_dtype = DataType(graph.Tensors(ker_idx).Type())
  ker_shape = ctx.get_shape_of_tensor_index_(ker_idx)
  _, KER_H, KER_W, _ = ker_shape

  # ASSUME: NHWC
  OFM_N, OFM_H, OFM_W, OFM_C = ctx.get_shape_of_tensor_index_(ofm_idx)

  return OperatorAbstraction(core.Operation.DepthwiseConv2D,
    attr={
      "OFM_N": OFM_N,
      "OFM_H": OFM_H,
      "OFM_W": OFM_W,
      "OFM_C": OFM_C,
      "KER_H": KER_H,
      "KER_W": KER_W,
      "WITH_BIAS": has_bias,
    },
    weights=[core.Tensor(shape=list(ker_shape), bitwidth=ker_dtype.bitwidth)],
  )

def avgpool(ctx: OperatorAbstractionContext):
  operator = ctx.operator.raw

  assert operator.BuiltinOptionsType() == tflite.BuiltinOptions.Pool2DOptions
  option = operator.BuiltinOptions()
  pool_option = tflite.Pool2DOptions()
  pool_option.Init(option.Bytes, option.Pos)

  assert operator.OutputsLength() == 1
  ofm_idx = operator.Outputs(0)

  # ASSUME: NHWC
  OFM_N, OFM_H, OFM_W, OFM_C = ctx.get_shape_of_tensor_index_(ofm_idx)

  FLT_H = pool_option.FilterHeight()
  FLT_W = pool_option.FilterWidth()

  return OperatorAbstraction(core.Operation.AvgPool,
    attr={
      "OFM_N": OFM_N,
      "OFM_H": OFM_H,
      "OFM_W": OFM_W,
      "OFM_C": OFM_C,
      "FLT_H": FLT_H,
      "FLT_W": FLT_W,
    },
  )

def maxpool(ctx: OperatorAbstractionContext):
  operator = ctx.operator.raw

  assert operator.BuiltinOptionsType() == tflite.BuiltinOptions.Pool2DOptions
  option = operator.BuiltinOptions()
  pool_option = tflite.Pool2DOptions()
  pool_option.Init(option.Bytes, option.Pos)

  assert operator.OutputsLength() == 1
  ofm_idx = operator.Outputs(0)

  # ASSUME: NHWC
  OFM_N, OFM_H, OFM_W, OFM_C = ctx.get_shape_of_tensor_index_(ofm_idx)

  FLT_H = pool_option.FilterHeight()
  FLT_W = pool_option.FilterWidth()

  return OperatorAbstraction(core.Operation.MaxPool,
    attr={
      "OFM_N": OFM_N,
      "OFM_H": OFM_H,
      "OFM_W": OFM_W,
      "OFM_C": OFM_C,
      "FLT_H": FLT_H,
      "FLT_W": FLT_W,
    },
  )

def eltwise(ctx: OperatorAbstractionContext):
  operator = ctx.operator.raw

  assert operator.OutputsLength() == 1
  ofm_idx = operator.Outputs(0)

  ofm_shape = ctx.get_shape_of_tensor_index_(ofm_idx)

  return OperatorAbstraction(core.Operation.EWO,
    attr={ "OUT_COUNT": ofm_shape.prod() },
  )

# Not a compute
def no_compute(ctx):
  return OperatorAbstraction(core.Operation.MemoryTransfer)

def not_implemented(ctx):
  return OperatorAbstraction(core.Operation.Other)

def ignored(ctx):
  return OperatorAbstraction(core.Operation.Other)


class OperationTranslatorRegistry:
  def __init__(self):
    self._models = {
      # Convolutional
      tflite.BuiltinOperator.CONV_2D: conv2d,
      tflite.BuiltinOperator.DEPTHWISE_CONV_2D: dconv2d,

      # Pooling
      tflite.BuiltinOperator.AVERAGE_POOL_2D: avgpool,
      tflite.BuiltinOperator.MAX_POOL_2D: maxpool,

      # Element-wise
      tflite.BuiltinOperator.ADD: eltwise,
      tflite.BuiltinOperator.MUL: eltwise,

      # NAC: Not a compute
      tflite.BuiltinOperator.PAD: no_compute,
      tflite.BuiltinOperator.RESHAPE: no_compute,
      tflite.BuiltinOperator.SQUEEZE: no_compute,
      tflite.BuiltinOperator.CONCATENATION: no_compute,

      tflite.BuiltinOperator.MEAN: not_implemented,

      # Ignored
      tflite.BuiltinOperator.SOFTMAX: ignored,
    }

  def abstract(self, operator: Operator):
    raw_operator = operator.raw
    raw_model = operator.model.raw

    opcode = raw_model.OperatorCodes(raw_operator.OpcodeIndex()).BuiltinCode()
    assert opcode is not None

    try:
      f = self._models[opcode]
    except KeyError:
      print(tflite.BUILTIN_OPCODE2NAME[opcode])
      raise

    return f(OperatorAbstractionContext(operator))

class OperatorAbstractionFactory:
  def __init__(self):
    self._registry = OperationTranslatorRegistry()
    self._cost_model = core.SymbolicOperationCostEstimator.get_default_estimator()

  def __call__(self, tfl_operator: Operator):
    operator = tfl_operator.raw
    registry = self._registry

    op_abstraction = registry.abstract(tfl_operator)

    core_layer = core.Layer(op_abstraction.kind)

    cost_info = self._cost_model.lookup(core_layer.operation)

    cost_attr = op_abstraction.attr
    cost_expr = cost_info.expr
    cost_value = eval(cost_expr, cost_attr.copy(), {})

    cost_note = "" if cost_info.note is None else cost_info.note

    core_layer.compute_cost = core.LayerComputeCost(
      attr=cost_attr,
      expr=cost_expr,
      value=cost_value,
      note=cost_note,
    )

    core_layer.weight = core.LayerWeight(op_abstraction.weights)

    return core_layer

## DESIGN IDEA
#
# Let's restrict client's visibility to this helepr!
def import_file_at(tfl_path):
  tfl_model = Model.from_file_at(tfl_path)
  assert tfl_model.raw.SubgraphsLength() == 1
  tfl_graph = tfl_model.graph(0)

  def as_port(index):
    tensor = tfl_graph.raw.Tensors(index)

    dtype = DataType(tensor.Type())
    shape = tensor.ShapeAsNumpy()

    return core.Tensor(shape=list(shape), bitwidth=dtype.bitwidth)

  inputs = [as_port(index) for index in tfl_graph.raw.InputsAsNumpy()]
  outputs = [as_port(index) for index in tfl_graph.raw.OutputsAsNumpy()]

  tfl2a_layer_convert = OperatorAbstractionFactory()

  layers = []

  for operator_idx in range(0, tfl_graph.raw.OperatorsLength()):
    tfl_operator = tfl_graph.operator(operator_idx)

    l = tfl2a_layer_convert(tfl_operator)
    l.origin = str(operator_idx)

    layers.append(l)

  return core.Model(inputs=inputs, outputs=outputs, layers=layers)
