# pylint: disable=missing-module-docstring, missing-function-docstring, fixme

# Standard Libraries (3.6)
from pathlib import Path


# From 3rd-party Libraries
import click
import yaml

def rcfile_type():
  return click.Path(exists=True, dir_okay=False, path_type=Path)
# def rcfile_type


@click.command()
@click.option('--rcfile', required=True, type=rcfile_type())
def entrypoint(rcfile):
  with open(rcfile, encoding='utf-8') as f: # pylint: disable=invalid-name
    lint_items = yaml.load(f, Loader=yaml.FullLoader)
  # with: END

  rcdir = rcfile.parent
  print(rcdir) # FIXME Remove this

  print(lint_items) # FIXME Remove

  # TODO Validate lint_items first

  # Build lint plan: i.e. file -> actors
  lint_plan = { }

  # Build 'file path' -> 'rules' first (to support override)
  # Q. memory issue?
  for lint_item in lint_items:

    # TODO Show error if 'pattern' is missing
    # Q. How to get a line number for this object?

    glob_pat = lint_item['pattern']
    print(glob_pat)

    lint_actors = [ ]

    if 'rules' in lint_item: # 'rules' may not exist
      lint_rules = lint_item['rules']

      # Lower rules
      #
      # Why? Rules may be of array or dict type
      # Why dict? To make it easy to parametric rules (e.g. line-should-not-exceed)
      if isinstance(lint_rules, list):
        lint_rules_lowered = { }

        for name in lint_rules:
          lint_rules_lowered[name] = { }
        # for: END

        lint_rules = lint_rules_lowered
      # if: END

      if not isinstance(lint_rules, dict):
        raise Exception('Invalid')
      # if: END

      # TODO Create actors from each rule
      lint_actors = lint_rules
    # if: END

    # Do not skip update below even if lint_actors is empty
    # This indicates

    # Do globbing from the directory that includes .txlintrc
    for file_path in list(rcfile.parent.glob(glob_pat)):
      lint_plan[file_path] = lint_actors
    # for: END
  # for: END

  #print(lint_plan)

  compact_lint_plan = { path:actors for path,actors in lint_plan.items() if len(actors) > 0 }
  print(compact_lint_plan)

  # TODO Execute it!
# def entrypoint: END


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
