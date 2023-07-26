# Motivation
#
# https://blog.tensorflow.org/2020/04/whats-new-in-tensorflow-lite-from-devsummit-2020.html mentions ALBERT-Lite.
import tensorflow as tf
# TensorFlow gets stuck with the following error without tensorflow_text:
# > Op type not registered 'NormalizeUTF8' in binary running
import tensorflow_text as tf_text
import tensorflow_hub as hub

# Tested Environment
assert tf.__version__ == '2.7.1'
assert tf_text.__version__ == '2.7.3'

# How I get to know this code fragment?
#
# https://github.com/tensorflow/models/blob/master/official/nlp/docs/pretrained_models.md
# -> https://tfhub.dev/tensorflow/albert_en_base/3
#
# https://tfhub.dev/tensorflow/albert_en_base/3 includes this fragment
preprocessor = hub.KerasLayer("http://tfhub.dev/tensorflow/albert_en_preprocess/3")
encoder = hub.KerasLayer("https://tfhub.dev/tensorflow/albert_en_base/3")

text_input = tf.keras.layers.Input(shape=(), dtype=tf.string)
encoder_inputs = preprocessor(text_input)
outputs = encoder(encoder_inputs)
pooled_output = outputs["pooled_output"]

def create_embedding_model():
  return tf.keras.Model(text_input, pooled_output)

def create_preprocess_model():
  return tf.keras.Model(text_input, encoder_inputs)

def create_encode_model():
  return tf.keras.Model(encoder_inputs, pooled_output)

def export_to_tflite(keras_model, output_path):
  converter = tf.lite.TFLiteConverter.from_keras_model(keras_model)

  # To use tf.Einsum
  converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS, tf.lite.OpsSet.SELECT_TF_OPS]

  tflite_model = converter.convert()

  with open(output_path, 'wb') as f:
    f.write(tflite_model)
# def export_to_tflite: END

export_to_tflite(create_encode_model(), 'models.mine/ALBERT.tflite')
