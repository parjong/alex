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

    template_globals = { }

    # Possible extensions
    # - bplate_version (to support api extension)
    # - bplate_primitives
    #   - returns the list of supported primitives
    #   - an alternative to bplate_version
    # - bplate_parameters (to support parametric template)
    template_globals['bplate_output_dir'] = output_dir
    template_globals['bplate_template_dir'] = template_dir

    # Create a fresh dict (to avoid name conflict between templates)
    template_locals = { }

    # exec(object, globals, locals)
    exec(template_code, template_globals, template_locals)
  # def interp: END
# class Interpreter: END
