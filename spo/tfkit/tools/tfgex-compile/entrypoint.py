from argparse import ArgumentParser

def tfgex_compile(tfgex_path, tflite_path=None):
  assert tflite_path is not None

  from pathlib import Path
  import warnings

  # To suppress FutureWarning from numpy
  warnings.simplefilter(action='ignore', category=FutureWarning)

  import tensorflow as tf

  class Session:
    def __init__(self):
      self._inputs = [ ]
      self._outputs = [ ]

    def set_inputs(self, *args):
      self._inputs = args

    def set_outputs(self, *args):
      self._outputs = args

    def export(self, tflite_path):
      with tf.compat.v1.Session() as sess:
        tflite_converter = tf.compat.v1.lite.TFLiteConverter.from_session(sess, self._inputs, self._outputs)
        tflite_content = tflite_converter.convert()

      with open(tflite_path, 'wb') as f:
        f.write(tflite_content)
  # class Session

  with tf.Graph().as_default() as g:
    sess = Session()

    # Compile .tfgex for 'exec'
    tfgex_code = compile(Path(tfgex_path).read_text(), args.tfgex_path, 'exec')

    # tfgex primitives
    primitives = { }

    primitives['tfgex_set_inputs'] = lambda *args: sess.set_inputs(*args)
    primitives['tfgex_set_outputs'] = lambda *args: sess.set_outputs(*args)

    # exec(object, globals, locals)
    exec(tfgex_code, primitives, {})

    sess.export(tflite_path)
# def tfgex_compile

parser = ArgumentParser()

parser.add_argument('-o', dest='tflite_path', metavar='<path/to/tflite>', required=True)
parser.add_argument('tfgex_path', metavar='<path/to/tfgex>')

args = parser.parse_args()

tfgex_compile(args.tfgex_path, tflite_path=args.tflite_path)
