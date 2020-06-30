from . import core
import logging
import tensorflow as tf

class Format(core.Format):
    def __init__(self):
        pass

class Signature:
    def __init__(self, detail):
        assert 'dtype' in detail
        assert 'shape' in detail
        assert 'index' in detail

        self.dtype = detail['dtype']
        self.shape = detail['shape']
        self.index = detail['index']

        logging.info('detail: {}'.format(detail))

class Model:
    """TF Lite Model"""

    def __init__(self, content):
        self.format = Format()
        self.content = content
        # TODO Add quantization field
        # quantization = Unknown | None | FullQuantization | DummyQuantization | PostTrainingQuantization

        interpreter = tf.lite.Interpreter(model_content=content)

        self.input_signature = [Signature(detail) for detail in interpreter.get_input_details()]
        self.output_signature = [Signature(detail) for detail in interpreter.get_output_details()]

        pass

    def input(self, n):
        return self.input_signature[n]

    def output(self, n):
        return self.output_signature[n]

    def infer(self, input_tuple):
        # Check "https://www.tensorflow.org/lite/guide/inference" for details
        interpreter = tf.lite.Interpreter(model_content=self.content)
        interpreter.allocate_tensors()

        for n, input_data in enumerate(input_tuple):
            interpreter.set_tensor(self.input(n).index, input_data)

        interpreter.invoke()

        return [interpreter.get_tensor(sig.index) for sig in self.output_signature]
