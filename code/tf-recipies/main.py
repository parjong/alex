import tensorflow as tf
import importlib
import argparse

parser = argparse.ArgumentParser(description='Process recipies')

parser.add_argument('recipes', metavar='RECIPE', nargs='+')

args = parser.parse_args()

for recipe in args.recipes:
	print("Process " + recipe)
	tf.reset_default_graph()
        # https://stackoverflow.com/questions/37808866/proper-way-to-dynamically-import-a-module-with-relative-imports
	importlib.import_module("recipies." + recipe)
	print(tf.get_default_graph().as_graph_def())
        # TODO Save T/F GraphDef as "[RECIPE].pb" or "[RECIPE].pbtxt"
