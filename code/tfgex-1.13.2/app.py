import warnings

# To suppress FutureWarning from numpy
warnings.simplefilter(action='ignore', category=FutureWarning)

import tensorflow as tf
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--output-prefix', '-p', metavar='PREFIX', required=True)
parser.add_argument('--script', '-s', metavar='SCRIPT', required=True)
parser.add_argument('recipe', metavar='RECIPE')

args = parser.parse_args()

# Namespace(output_prefix='...', recipe='...', script='...')
recipe = args.recipe

# Reset TF Graph
tf.compat.v1.reset_default_graph()

# Reconstruct TF Graph from TF Graph recipe (.tfg)
#
# TODO Find a way to evaluate TF Grpah recipe without affecting the current scope
with open(args.recipe, 'r') as recipe:
   exec(recipe.read())

# Set up the runtime environment for TF Graph Export Script
output_type = None
output_prefix = args.output_prefix
output_suffix = None

def configure(mode):
    global output_type
    global output_suffix

    assert output_type is None

    # TODO Support more modes
    assert mode is 'tflite'

    output_type = 'tflite'
    output_suffix = 'tflite'

# TODO Suffix override
def export():
    global output_type
    global output_suffix

    assert output_type is 'tflite'

    global inputs
    global outputs

    with tf.compat.v1.Session() as sess:
        converter = tf.lite.TFLiteConverter.from_session(sess, inputs, outputs)
        # TODO Set inference_type
        # TODO Set inference_input_type
        # TODO Set quantized_input_stats
        # TODO Set default_ranges_stats
        tflite_model = converter.convert()

    output_path = '{}.{}'.format(output_prefix, output_suffix)
    with open(output_path, 'wb') as tflite:
        tflite.write(tflite_model)

# Read and evaluate TF Graph Export Script (.tfges)
with open(args.script, 'r') as script:
    exec(script.read())
