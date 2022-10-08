# Python Standard Library
from argparse import ArgumentParser

# External Library
import yaml

# Internal Modules
from mas.core import ModelInput, ModelConst, LayerOutput, ValueID
from mas.core import MASElem, MASModel, MASRunner

# EXPECTED INPUT
#
# { 'from': ..., 'ind': ... }
#
def to_value_ref(d):
  convert_function_registry = {
    ModelInput.prefix: lambda ind: (ModelInput, int(ind)),
    ModelConst.prefix: lambda ind: (ModelConst, str(ind)),
    LayerOutput.prefix: lambda ind: (LayerOutput, str(ind)),
  }

  convert = convert_function_registry[d['from']]
  src, ind = convert(d['index'])

  return ValueID(src, ind)

def to_elem_detail(d):
  return MASElem(d['type'], d['avgbit'])

def read_from(raw_data):
  m = MASModel(opset=raw_data['opset'])

  # Parse 'input'
  for input_ind, input_raw in enumerate(raw_data['input']):
    input_ref = ValueID(ModelInput, input_ind)

    elem = to_elem_detail(input_raw['elem'])
    dims = input_raw['dims']

    m.append_input(elem=elem, dims=dims)

  # Parse 'data'
  #
  # Q: What happens if there is a 'key' conflict?
  for data_key, data_raw in raw_data['data'].items():
    data_ref = ValueID(ModelConst, data_key)

    elem = to_elem_detail(data_raw['elem'])
    dims = data_raw['dims']

    m.append_data(name=data_key, elem=elem, dims=dims)

  # Parse 'layer'
  for layer_raw in raw_data['layer']:
    layer = m.append_layer()

    layer.op = layer_raw['op']

    # TODO Parse attr
    # TODO Parse data

    # Parse layer input
    for layer_input_raw in layer_raw['input']:
      value_id = to_value_ref(layer_input_raw)
      layer.add_input(value_id)

    # Parse layer output
    for layer_output_ind, layer_output_raw in enumerate(layer_raw['output']):
      value_id = ValueID(LayerOutput, f'{layer.ind}:{layer_output_ind}')

      elem = to_elem_detail(layer_output_raw['elem'])
      dims = layer_output_raw['dims']

      m.create_value(vid=value_id, elem=elem, dims=dims)
      layer.add_output(value_id)
  # Parse 'layer' - Done

  for output_raw in raw_data['output']:
    value_id = to_value_ref(output_raw)
    m.append_output(value_id)

  return m
# end read_from

# CLI
parser = ArgumentParser(description='Analyze .tflite model with .mas scrikpts')
parser.add_argument('-m', '--model-path', metavar='PATH', required=True, dest='MODEL_PATH')

args, rest = parser.parse_known_args()

with open(args.MODEL_PATH, 'r') as f:
  raw_data = yaml.safe_load(f)
  mas_model = read_from(raw_data)

runner = MASRunner(mas_model)

for script_path in rest:
  runner.run(script_path)
