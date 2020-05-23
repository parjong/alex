# A Tool Generates something from a suite of TensorFlow Graph Recipes
# (maybe tfgraph-chef)?

import tensorflow as tf
import importlib
import argparse

assert tf.__version__ == '1.13.2'

# for each TF graph recipe G in '<DIR>'
#   if G satisfies '<COND>'
#   do '<ACTION>'
#
# TODO Take "the base directory" as an argument
# TODO Allow users to select the input graphs
#   all examples in the directory
#   selected examples in the directory
# TODO Allowe
for example in ['A', 'B']:
        tf.compat.v1.reset_default_graph()
        m = importlib.import_module(example)

        print("Generate '" + example + ".pbtxt'")
        with open(example + ".pbtxt", "w") as f:
            f.write(str(tf.compat.v1.get_default_graph().as_graph_def(add_shapes=True)))
        print("Generate '" + example + ".pbtxt' - Done")

        # How to create a TFLITE (F32) from TF Graph
        #
        # Reference
        # - https://www.tensorflow.org/api_docs/python/tf/compat/v1/Session
        # - https://github.com/tensorflow/docs/blob/r1.13/site/en/api_docs/python/tf/lite/TFLiteConverter.md
        print("Generate '" + example + ".f32.tflite'")
        with tf.compat.v1.Session() as sess:
                converter = tf.lite.TFLiteConverter.from_session(sess, m.inputs, m.outputs)
                tflite_model = converter.convert()
                open(example + ".f32.tflite", "wb").write(tflite_model)
        print("Generate '" + example + ".f32.tflite' - Done")

        # How to create a TensorFlow Lite from T/F Graph
        #
        # Reference
        # - https://github.com/tensorflow/docs/blob/r1.13/site/en/api_docs/python/tf/lite/TFLiteConverter.md
        # - https://stackoverflow.com/questions/54830869/understanding-tf-contrib-lite-tfliteconverter-quantization-parameters
        print("Generate '" + example + ".q8.tflite'")
        with tf.compat.v1.Session() as sess:
                converter = tf.lite.TFLiteConverter.from_session(sess, m.inputs, m.outputs)
                # Use 'dummy' quantization
                converter.inference_type = tf.uint8
                converter.quantized_input_stats = {}
                for tensor in m.inputs:
                        converter.quantized_input_stats[tensor.op.name] = (128, 127)
                converter.default_ranges_stats = (-128, 127)
                tflite_model = converter.convert()
                open(example + ".q8.tflite", "wb").write(tflite_model)
        print("Generate '" + example + ".q8.tflite' - Done")
