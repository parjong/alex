"""bplate core objects"""
from pathlib import Path

class Interpreter:
  """bplate template interpreter"""
  def __init__(self, output_dir):
    assert isinstance(output_dir, Path)
    self._output_dir = output_dir
  # def __init__: END

  def interp(self, template_dir):
    """load a template from a given directory"""
    assert isinstance(template_dir, Path)

    output_dir = self._output_dir

    template_path = template_dir / 'bplate.template'
    template_code = compile(template_path.read_text(), template_path, 'exec')

    # Define primitives (except bplate_primitives)
    template_primitives = { }

    template_primitives['bplate_output_dir'] = output_dir
    template_primitives['bplate_template_dir'] = template_dir
    # Possible extension: bplate_parameters
    #
    # This API allows users to write a parametric template

    # Create globals
    template_globals = { }

    template_globals.update(template_primitives)
    # This extra API permits compatibility check
    template_globals['bplate_primitives'] = list(template_primitives.keys())

    # Define __file__ to improve error message
    # Ref: https://docs.python.org/3.7/reference/import.html?highlight=__file__#file__
    template_globals['__file__'] = str(template_path)

    # Create a fresh dict (to avoid name conflict between templates)
    template_locals = { }

    # exec(object, globals, locals)
    exec(template_code, template_globals, template_locals)
  # def interp: END
# class Interpreter: END
