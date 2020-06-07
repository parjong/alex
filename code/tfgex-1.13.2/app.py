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

output_type = None
output_prefix = args.output_prefix
output_suffix = None

def configure(mode):
    global output_type
    global output_suffix

    assert output_type is None

    # TODO Extend this!
    assert mode is 'tflite'

    output_type = 'tflite'
    output_suffix = 'tflite'

def commit():
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

    # TODO Suffix override
    output_path = '{}.{}'.format(output_prefix, output_suffix)
    with open(output_path, 'wb') as tflite:
        tflite.write(tflite_model)

###
###
###
tf.compat.v1.reset_default_graph()

with open(args.recipe, 'r') as recipe:
   exec(recipe.read())

with open(args.script, 'r') as script:
    exec(script.read())
