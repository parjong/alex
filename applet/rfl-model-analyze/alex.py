import rfl.core as core
import rfl.tflbridge as tflbridge

import click

import json

class ReporterContext:
  def __init__(self):
    self._path = None
    self._model = None

  @property
  def path(self):
    return self._path

  @path.setter
  def path(self, new_path: str):
    self._path = new_path

  @property
  def model(self):
    return self._model

  @model.setter
  def model(self, new_model: core.Model):
    self._model = new_model

class JSONReporter:
  def summarize_tensor(tensor: core.Tensor):
    return {
      'shape': [int(dim) for dim in tensor.shape],
      'bitwidth': {
        'value': tensor.bitwidth,
        'note': 'The average number of bits used to encode each element (= bit size / element count)'
      }
    }

  def summarize_layer(layer: core.Layer):
    compute_cost_report = {
      'attr': { k:str(v) for (k, v) in layer.compute_cost.attr.items() },
      'expr': layer.compute_cost.expr,
      'value': str(layer.compute_cost.value),
    }

    if layer.compute_cost.note is not None:
      compute_cost_report['note'] = layer.compute_cost.note

    return {
      'origin': layer.origin,
      'operation': layer.operation.name,
      'compute_cost': compute_cost_report,
      'weight': [JSONReporter.summarize_tensor(t) for t in layer.weight],
    }

  def report(self, ctx: ReporterContext):
    path = ctx.path
    model = ctx.model

    W = sum([l.compute_cost.value for l in model.layers])

    model_input_size_in_byte = sum([i.get_size_in_byte() for i in model.inputs])
    model_output_size_in_byte = sum([o.get_size_in_byte() for o in model.outputs])
    model_weight_size_in_byte = sum([l.weight.get_size_in_byte() for l in model.layers])

    Qmin = sum([model_input_size_in_byte, model_output_size_in_byte, model_weight_size_in_byte])
    Imax = W / Qmin

    meta = {
      'path': str(path),
    }

    summary = {
      'W': { 'value': str(W), 'unit': 'OPS', 'note': 'The number of operations' },
      'Qmin': {
        'value': str(Qmin),
        'unit': 'B',
        'note': 'The minimal number of byte transfer (Input size + Output size + Weight size)'
      },
      'Imax': { 'value': str(Imax), 'unit': 'OPS/B', 'note': 'W / Qmin' },
    }

    return json.dumps({
      'meta': meta,
      'summary': summary,
      'detail': {
        'input': [JSONReporter.summarize_tensor(i) for i in model.inputs],
        'output': [JSONReporter.summarize_tensor(o) for o in model.outputs],
        'layer': [JSONReporter.summarize_layer(l) for l in model.layers],
      }
    })

@click.command()
@click.argument("path", type=click.Path(exists=True, dir_okay=False))
def cli(path):
  # TODO Check file extension and select importer
  core_model = tflbridge.import_file_at(path)
  # TODO Select reporter with command-line option
  reporter = JSONReporter()

  ctx = ReporterContext()

  ctx.model = core_model
  ctx.path = str(path)

  report = reporter.report(ctx)

  print(report)

cli()
