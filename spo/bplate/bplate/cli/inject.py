"""bplate-inject command-line interface"""
import argparse

from pathlib import Path
from sys import stderr

import bplate.core

def run():
  """bplate cli entrypoint"""
  parser = argparse.ArgumentParser()

  parser.add_argument('-o', '--output', dest='output', required=True,
                      help='bplate output directory')
  parser.add_argument('templates', metavar='template', type=str, nargs='+',
                      help='bplate template directory')

  args = parser.parse_args()

  output_path = Path(args.output)

  # bplate-inject requires output path to exist
  if not output_path.exists():
    print(f"error: invalid argument: '{output_path}' does not exist", file=stderr)
    return 1
  # if: END

  # bplate-inject requires output path to be a directory
  if not output_path.is_dir():
    print(f"error: invalid argument: '{output_path}' is not a directory", file=stderr)
    return 1
  # if: END

  bplate_interpreter = bplate.core.Interpreter(output_path)

  for template in args.templates:
    template_path = Path(template)
    bplate_interpreter.interp(template_path)
  # for template: END

  return 0
# def run: END

if __name__ == "__main__":
  run()
