import tensorflow as tf

print("Hello from PLUGIN")

tf_input = tf.placeholder(dtype=tf.float32, shape=(1, 1))
tf_relu = tf.nn.relu(tf_input)
