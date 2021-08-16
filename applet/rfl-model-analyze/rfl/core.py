from enum import Enum, unique, auto
import math

@unique
class Operation(Enum):
  # Attributes
  #
  # - OFM_N
  # - OFM_H
  # - OFM_W
  # - OFM_C
  # - KER_H
  # - KER_W
  # - KER_I
  # - WITH_BIAS
  Conv2D = auto()

  # Attributes
  #
  # - OFM_N
  # - OFM_H
  # - OFM_W
  # - OFM_C
  # - KER_H
  # - KER_W
  # - KER_I
  # - WITH_BIAS
  DepthwiseConv2D = auto()

  AvgPool = auto()
  MaxPool = auto()

  # Attributes
  #
  # - OUT_COUNT
  #
  # NOTE: EWO is an abbriviation of Element-Wise Operation
  EWO = auto()

  # Attributes
  #
  # None
  #
  MemoryTransfer = auto()


  # Attributes
  #
  # None
  #
  Other = auto()


class SymbolicOperationCost:
  """Symbolic Operation Cost"""
  def __init__(self, expr, note):
    self._expr = expr
    self._note = note

  @property
  def expr(self):
    return self._expr

  @property
  def note(self):
    return self._note


class SymbolicOperationCostEstimator:
  def __init__(self):
    self._exprs = {}

  def add(self, op, expr, note=None):
    self._exprs[op] = SymbolicOperationCost(expr, note)

  def lookup(self, t):
    return self._exprs[t]

  def get_default_estimator():
    cost_model = SymbolicOperationCostEstimator()

    cost_model.add(Operation.Other, '0', note='Unsupported operation')
    cost_model.add(Operation.MemoryTransfer, '0', note='Memory transfer operation')

    cost_model.add(Operation.Conv2D, '(OFM_N * OFM_H * OFM_W) * (2 * KER_H * KER_W * KER_I + (1 if WITH_BIAS else 0))')
    cost_model.add(Operation.DepthwiseConv2D, '(OFM_N * OFM_H * OFM_W) * (2 * KER_H * KER_W + (1 if WITH_BIAS else 0))')
    # For each pixel,
    #   compute "ACCUM = ACCUM + X / (FLT_SIZE)" for FLT_SIZE times
    cost_model.add(Operation.AvgPool, '(OFM_N * OFM_H * OFM_W * OFM_C) * (2 * FLT_H * FLT_W)')
    cost_model.add(Operation.MaxPool, '(OFM_N * OFM_H * OFM_W * OFM_C) * (FLT_H * FLT_W - 1)')

    cost_model.add(Operation.EWO, 'OUT_COUNT * 1')

    return cost_model


class Tensor:
  def __init__(self, shape=None, bitwidth=None):
    assert shape is not None
    assert bitwidth is not None

    self._shape = shape
    self._bitwidth = bitwidth

  @property
  def shape(self):
    return self._shape

  @property
  def bitwidth(self):
    # NOTE It is possible to use a fractional number (e.g. compressed data)
    return self._bitwidth

  def get_size_in_byte(self):
    return math.prod(self.shape) * (self.bitwidth / 8)


class LayerComputeCost:
  def __init__(self, attr=None, expr=None, value=None, note=None):
    self._attr = attr
    self._expr = expr
    self._value = value
    self._note= note

  @property
  def attr(self):
    return self._attr

  @property
  def expr(self):
    return self._expr

  @property
  def value(self):
    return self._value

  @property
  def note(self):
    return self._note


class LayerWeight:
  def __init__(self, tensors=[]):
    self._tensors = tensors

  def __iter__(self):
    return self._tensors.__iter__()

  def __getitem__(self, n):
    return self._tensors.__getitem__(n)

  def append(self, l):
    self._tensors.append(l)

  def get_size_in_byte(self):
    return sum([tensor.get_size_in_byte() for tensor in self._tensors])


class Layer:
  def __init__(self, operation: Operation):
    assert type(operation) is Operation
    # Describe the operation that this layer performs
    self._operation = operation

    self._compute_cost = None
    # Weight discribes
    self._weight = None

    self._origin = None # MUST

  @property
  def operation(self):
    return self._operation

  @property
  def origin(self):
    return self._origin

  @origin.setter
  def origin(self, new_origin: str):
    assert type(new_origin) is str
    self._origin = new_origin

  @property
  def compute_cost(self):
    return self._compute_cost

  @compute_cost.setter
  def compute_cost(self, new_compute_cost: LayerComputeCost):
    assert type(new_compute_cost) is LayerComputeCost
    self._compute_cost = new_compute_cost

  @property
  def weight(self):
    return self._weight

  @weight.setter
  def weight(self, new_weight: LayerWeight):
    assert type(new_weight) is LayerWeight
    self._weight = new_weight


class Model:
  def __init__(self, inputs=[], outputs=[], layers=[]):
    self._inputs = inputs
    self._outputs = outputs
    self._layers = layers

  @property
  def inputs(self):
    return self._inputs

  @property
  def outputs(self):
    return self._outputs

  @property
  def layers(self):
    return self._layers
