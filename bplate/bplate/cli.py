"""bplate command-line interface"""
import argparse

from pathlib import Path
from sys import stderr

import bplate

def run():
  """bplate cli entrypoint"""
  parser = argparse.ArgumentParser()

  parser.add_argument('-o', '--output', dest='output', required=True,
                      help='bplate output directory')
  parser.add_argument('templates', metavar='template', type=str, nargs='+',
                      help='bplate template directory')

  args = parser.parse_args()

  output_path = Path(args.output)

  if not output_path.exists():
    # Q. How to handle this case properly?
    #
    # One idea is to distinguish 'bplate-new' and 'bplate-inject'
    output_path.mkdir(parents=True)
  elif not output_path.is_dir():
    print(f'error: invalid argument: {output_path} is not a directory', file=stderr)
    return 1

  bplate_interpreter = bplate.core.Interpreter(output_path)

  for template in args.templates:
    template_path = Path(template)
    bplate_interpreter.interp(template_path)
  # for template: END

  return 0
# def run: END
