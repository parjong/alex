# https://tfhub.dev/tensorflow/mobilebert_en_uncased_L-24_H-128_B-512_A-4_F-4_OPT/1
import tensorflow as tf
# To resolve the following warning
# > Op type not registered 'CaseFoldUTF8' in binary
import tensorflow_text as tf_text
import tensorflow_hub as hub

# Tested Environment
assert tf.__version__ == '2.7.1'
assert tf_text.__version__ == '2.7.3'

# From https://tfhub.dev/tensorflow/mobilebert_en_uncased_L-24_H-128_B-512_A-4_F-4_OPT/1
text_input = tf.keras.layers.Input(shape=(), dtype=tf.string)
preprocessor = hub.KerasLayer(
    "https://tfhub.dev/tensorflow/bert_en_uncased_preprocess/3")
encoder_inputs = preprocessor(text_input)
encoder = hub.KerasLayer(
    "https://tfhub.dev/tensorflow/mobilebert_en_uncased_L-24_H-128_B-512_A-4_F-4_OPT/1",
    trainable=True)
outputs = encoder(encoder_inputs)
pooled_output = outputs["pooled_output"]      # [batch_size, 512].
sequence_output = outputs["sequence_output"]  # [batch_size, seq_length, 512].

embedding_model = tf.keras.Model(text_input, pooled_output)
sentences = tf.constant(["(your text here)"])
print(embedding_model(sentences))

converter = tf.lite.TFLiteConverter.from_keras_model(embedding_model)

tflite_model = converter.convert()

with open('models.mine/MobileBERT.tflite', 'wb') as f:
  f.write(tflite_model)
