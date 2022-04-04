from pathlib import Path

class SourceID:
  def __init__(self, prefix):
    self._prefix = prefix

  @property
  def prefix(self):
    return self._prefix

  def __eq__(self, another):
    if not type(another) == SourceID:
      return False
    return self.prefix == another.prefix

  def __hash__(self):
    return hash(self.prefix)
# class SourceID: END


# Possible Value Sources
ModelInput = SourceID('MI')
ModelConst = SourceID('MC')
LayerOutput = SourceID('LO')
# Possible Value Sources: END

class ValueID:
  """Value ID describes who creates this value"""
  def __init__(self, src, ind):
    # src = ModelInput | ModelConst | LayerOutput
    self._src = src

    # ModelInput => int (input index)
    # ModelConst => str (data name)
    # LayerOutput => str ('<layer index>:<output index>')
    self._ind = ind
  # End of __init__

  @property
  def src(self):
    return self._src

  @property
  def ind(self):
    return self._ind

  def __str__(self):
    return f'{self._src.prefix}!{str(self._ind)}'

  def __eq__(self, another):
    if not type(another) == ValueID:
      return False

    return self.src == another.src and self.ind == another.ind

  def __hash__(self):
    return hash((self.src, self.ind))
# class ValueID: END


class MASElem:
  """Abstracted Element for MAS"""
  def __init__(self, tname, avgbit):
    self._tname = tname
    self._avgbit = avgbit

  def tname(self):
    return self._tname

  def set_tname(self, value):
    self._tname = value

  def avgbit(self):
    return self._avgbit

  def set_avgbit(self, value):
    self._avgbit = value
# class MASElem: END


class MASElemEndpoint:
  def __init__(self, obj):
    assert type(obj) == MASElem
    self._obj = obj

  @property
  def tname(self):
    return self._obj.tname()

  @tname.setter
  def tname(self, value):
    self._obj.set_tname(value)

  @property
  def avgbit(self):
    return self._obj.avgbit()

  @avgbit.setter
  def avgbit(self, value):
    self._obj.set_avgbit(value)
# class MASElemEndpoint: END


class MASTensor:
  def __init__(self, vid=None, elem=None, dims=None):
    assert type(vid) == ValueID
    assert type(elem) == MASElem

    self._vid = vid
    self._elem = elem
    self._dims = dims
    pass

  def id(self):
    return self._vid

  def elem(self):
    return self._elem

  def rank(self):
    return len(self._dims)

  def dim(self, d):
    return self._dims[d]

  def dims(self):
    return self._dims
# class MASTensor: END


class MASTensorEndpoint:
  def __init__(self, obj):
    assert type(obj) == MASTensor
    self._obj = obj

  @property
  def id(self) -> ValueID:
    return self._obj.id()

  @property
  def elem(self) -> MASElemEndpoint:
    return MASElemEndpoint(self._obj.elem())

  @property
  def rank(self) -> int:
    return self._obj.rank()

  def dim(self, d) -> int:
    return self._obj.dim(d)

  @property
  def dims(self):
    return self._obj.dims()

  @property
  def elem_count(self):
    count = 1
    for dim in self.dims:
      count *= dim
    return count

  @property
  def byte_size(self):
    return self.elem_count * (self.elem.avgbit / 8)

  def is_model_const(self):
    return self.id.src == ModelConst

  def is_layer_output(self):
    return self.id.src == LayerOutput
# class MASTensorEndpoint: END


class MASLayer:
  def __init__(self, model):
    self._model = model

    self._ind = None
    self._op = None

    self._inputs = [ ]
    self._outputs = [ ]
    self._attrs = { }

  @property
  def model(self):
    return self._model

  @property
  def ind(self):
    return self._ind

  @ind.setter
  def ind(self, value):
    self._ind = value

  @property
  def op(self):
    return self._op

  @op.setter
  def op(self, value):
    self._op = value

  def inputs(self):
    return self._inputs

  def input(self, n):
    return self._inputs[n]

  def add_input(self, vid):
    assert type(vid) == ValueID
    self._inputs.append(vid)
    pass

  def outputs(self):
    return self._outputs

  def output(self, n):
    return self._outputs[n]

  def add_output(self, vid):
    assert type(vid) == ValueID
    self._outputs.append(vid)
    pass

  def attrs(self):
    return self._attrs

  def attr(self, k):
    return self._attrs[k]

  def set_attr(self, attr_name, attr_value):
    self._attrs[attr_name] = attr_value
    pass
# class MASLayer: END


class MASLayerEndpoint:
  def __init__(self, obj):
    assert type(obj) == MASLayer
    self._obj = obj

  @property
  def ind(self) -> int:
    """Layer Index"""
    return self._obj.ind

  @property
  def op(self) -> str:
    """Layer Operation"""
    return self._obj.op

  @property
  def input_count(self) -> int:
    return len(self._obj.inputs())

  def input(self, n) -> MASTensorEndpoint:
    symtbl = self._obj.model.symtbl()
    return MASTensorEndpoint(symtbl[self._obj.input(n)])

  @property
  def inputs(self) -> list:
    return [ self.input(n) for n in range(0, self.input_count) ]

  @property
  def output_count(self) -> int:
    return len(self._obj.outputs())

  def output(self, n) -> MASTensorEndpoint:
    symtbl = self._obj.model.symtbl()
    return MASTensorEndpoint(symtbl[self._obj.output(n)])

  @property
  def outputs(self) -> list:
    return [ self.output(n) for n in range(0, self.output_count) ]

  @property
  def attr_keys(self):
    return self._obj.attrs().keys()

  def attr(self, k):
    return self._obj.attr(k)

  @property
  def attr_items(self):
    return self._obj.attrs().items()

  # TODO Add lcon_count property and lcon(n) method
# class MASLayerEndpoint: END


class MASModel:
  def __init__(self, opset=None):
    assert opset is not None

    self._opset = opset

    # Symbol Table: Value Ref -> ValueDetail
    self._symtbl = { }

    # VID list
    self._inputs = [ ]
    # (NAME, VID) dict
    self._data = { }
    # Layer list
    self._layers = [ ]
    # VID list
    self._outputs = [ ]
  # def __init__: END

  def symtbl(self):
    return self._symtbl

  # Update methods
  def create_value(self, vid=None, elem=None, dims=None):
    value_ref = vid
    value_detail = MASTensor(vid=vid, elem=elem, dims=dims)

    self._symtbl[value_ref] = value_detail

    return value_detail

  def append_input(self, elem=None, dims=None):
    input_ind = len(self._inputs)
    input_vid = ValueID(ModelInput, input_ind)

    self.create_value(vid=input_vid, elem=elem, dims=dims)
    self._inputs.append(input_vid)

    return input_vid

  def append_data(self, name=None, elem=None, dims=None):
    data_key = name
    data_vid = ValueID(ModelConst, data_key)

    data_detail = self.create_value(vid=data_vid, elem=elem, dims=dims)
    self._data[data_key] = data_vid

    return data_vid

  def append_layer(self):
    layer = MASLayer(self)

    layer.ind = len(self._layers)
    self._layers.append(layer)

    return layer

  def append_output(self, vid):
    self._outputs.append(vid)
    pass

  ## Get Methods
  def opset(self):
    return self._opset

  def value_info(self, vid) -> MASTensor:
    try:
      return self._symtbl[vid]
    except:
      print(f'lookup failure: {vid}')
      raise

  def input_count(self):
    return len(self._inputs)

  def input_id(self, n):
    return self._inputs[n]

  def data_keys(self):
    return self._data.keys()

  def data_id(self, data_key):
    return self._data[data_key]

  def layer_count(self):
    return len(self._layers)

  def layer_detail(self, n):
    return self._layers[n]

  def output_count(self):
    return len(self._outputs)

  def output_id(self, n):
    return self._outputs[n]
# class MASModel: END


class MASModelEndpoint:
  """A set of Model properties visible from MAS scripts"""
  def __init__(self, model):
    assert type(model) == MASModel
    self._model = model

  @property
  def opset(self) -> str:
    return self._model.opset()

  def value(self, vid: ValueID) -> MASTensorEndpoint:
    assert type(vid) == ValueID
    return MASTensorEndpoint(self._model.value_info(vid))

  @property
  def input_count(self) -> int:
    return self._model.input_count()

  def input(self, n: int) -> MASTensorEndpoint:
    return self.value(self._model.input_id(n))

  @property
  def inputs(self) -> list:
    return [ self.input(n) for n in range(0, self.input_count) ]

  @property
  def mcon_keys(self):
    return self._model.data_keys()

  def mcon(self, k: str) -> MASTensorEndpoint:
    return self.value(self._model.data_id(k))

  @property
  def layer_count(self):
    return self._model.layer_count()

  def layer(self, n: int) -> MASLayerEndpoint:
    return MASLayerEndpoint(self._model.layer_detail(n))

  @property
  def layers(self) -> list:
    return [ self.layer(n) for n in range(0, self.layer_count) ]

  @property
  def output_count(self):
    return self._model.output_count()

  def output(self, n: int) -> MASTensorEndpoint:
    return self.value(self._model.output_id(n))

  @property
  def outputs(self) -> list:
    return [ self.output(n) for n in range(0, self.output_count) ]
# class MASModelEndpoint: END


class MASSession:
  def __init__(self, model):
    assert type(model) == MASModel

    self._model = model
    # Create an empty dict
    self._attrs = { }
  # def __init__: END

  @property
  def model(self) -> MASModel:
    return self._model
  # def model: END

  @property
  def attrs(self):
    return self._attrs
# class MASSession: END


class MASSessionEndpoint:
  def __init__(self, sess):
    assert type(sess) == MASSession
    self._sess = sess
  # def __init__: END

  def get_model(self) -> MASModelEndpoint:
    return MASModelEndpoint(self._sess.model)

  @property
  def model(self) -> MASModelEndpoint:
    return self.get_model()

  def has_attr(self, k):
    return k in self._sess.attrs

  def get_attr(self, k):
    return self._sess.attrs[k]

  def set_attr(self, k, v):
    assert type(k) is str
    assert k not in self._sess.attrs
    # NOTE: v can be a value of any type
    self._sess.attrs[k] = v

  # DESIGN NOTE: Why is this necessary?
  #
  # This helper makes it possible to resolve name conflicts between multiples .mas scripts.
  #
  # Let's assume that model analyst X wants to create a analysis report.
  #
  # X wants to combine a .mas script from developer A and another .mas script from devloper B,
  # but their script returns its analysis result with the same name 'K'.
  #
  # This 'rename_attr' helper allows X to resolve this name conflict as below:
  # 1. Run the .mas script from deverloper A
  # 2. Run X's own .mas script which renames 'K' as 'AK'
  # 3. Run the .mas script from deverloper B
  # 4. Run X's own .mas script which reads 'AK' and 'K'
  def rename_attr(self, old_k: str, new_k: str):
    assert type(old_k) is str
    assert type(new_k) is str
    assert old_k in self._sess.attrs

    value = self._sess.attrs.pop(old_k)
    self._sess.attrs[new_k] = value
  # def rename_attr: END

  def attr(self, k):
    return self.get_attr(k)
# class MASSessionEndpoint: END


class MASRunner:
  def __init__(self, model):
    assert type(model) == MASModel

    self._sess = MASSession(model)
  # def __init__

  def run(self, script_path):
    # Let's minimize the number of primitives to avoid potential conflicts!
    primitives = {
      'get_mas_session': lambda: MASSessionEndpoint(self._sess)
    }

    # Compile script for 'exec'
    code = compile(Path(script_path).read_text(), script_path, 'exec')

    # exec(object, globals, locals)
    #
    # Set 'locals' as empty in order to run each script in isolation
    exec(code, primitives, {})
  # def run
# class MASRunner
