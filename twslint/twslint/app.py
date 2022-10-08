"""Lint trailing whitespaces

twslint --rcfile <path/to/rcfile> <TARGET 1> <TARGET 2> ...

DESIGN NOTE: Why twslint takes targets?

This design makes it simple to integrate external filters.
- e.g. Check files changed by last git commit
"""
# pylint: disable=missing-class-docstring, missing-function-docstring
# pylint: disable=too-few-public-methods, fixme

# Standard Libraries (3.6)
import fileinput
from pathlib import Path


# From 3rd-party Libraries
import click # See https://click.palletsprojects.com/en/8.0.x/arguments/
import yaml


def rcfile_type():
  kwargs={
    'exists': True,
    'file_okay': True,
    'dir_okay': False,
    'path_type': Path,
  }
  return click.Path(**kwargs)
# def rcfile_type: END


def target_type():
  kwargs={
    'exists': True,
    'file_okay': True,
    'dir_okay': True,
    'path_type': Path,
  }
  return click.Path(**kwargs)
# def target_type: END


class TargetInterpreter:
  """Interpret twslint arguments

  If TARGET points to a directory, twslint will interpret it as '{TRAGET}/**/*'
  If TARGET points to a file, twslint will interpret it as '{TARGET}'
  """
  def interpret(self, targets): # pylint: disable=no-self-use
    fileset = set()

    for target in targets:
      if target.is_dir():
        fileset |= set(target.glob('**/*'))
      else:
        assert target.is_file() # FIX CALLER UNLESS
        fileset.add(target)
      # if
    # for: END

    # ENSURE: For all 'f' in 'files, 'f.is_file()' returns True
    return fileset
  # def interpret_targets: END
# class TargetInterpreter: END

class SelectionInterpreter:
  def __init__(self, base_dir):
    self._base_dir = base_dir
  # def __init__: END


  def interpret(self, selection):
    fileset = set()

    action_registry = {
      'include': fileset.update,
      'exclude': fileset.difference_update,
    }

    for entry in selection:
      assert 'pattern' in entry
      assert 'action' in entry

      pattern = entry['pattern']
      action = entry['action']

      items = self._base_dir.glob(pattern)

      update_items = action_registry[action]
      update_items(items)
    # for: END

    return fileset
  # def interpret: END
# class SelectionInterpreter: END

@click.command()
@click.option('--rcfile', required=True, type=rcfile_type())
@click.argument('targets', nargs=-1, type=target_type())
def entrypoint(rcfile, targets):
  base_dir = rcfile.parent

  target_interp = TargetInterpreter()
  selection_interp = SelectionInterpreter(base_dir)

  # Open rcfile
  with open(rcfile, encoding='utf-8') as f: # pylint: disable=invalid-name
    rcdata = yaml.load(f, Loader=yaml.FullLoader)
  # with: END
  assert 'selection' in rcdata # Warn that .twslintrc is invalid

  fileset_by_target = target_interp.interpret(targets)
  fileset_by_rcfile = selection_interp.interpret(rcdata['selection'])
  effective_fileset = fileset_by_target & fileset_by_rcfile

  with fileinput.input(files=effective_fileset, inplace = True) as f: # pylint: disable=invalid-name
    for line in f:
      print(line.rstrip())
    # for: END
  # with: END

  return 0

# Idea: Use 'fileinput' to do in-place update!
#
# https://docs.python.org/ko/3.6/library/fileinput.html


# Idea: Use 'glob' to match
#
# https://docs.python.org/ko/3.6/library/glob.html


# Q: How to get line number
#
# [1] suggests to derive pyyaml Loader and override 'construct-mapping'
#
# [1] https://stackoverflow.com/questions/13319067/parsing-yaml-return-with-line-number
# [2] https://github.com/yaml/pyyaml/issues/456
