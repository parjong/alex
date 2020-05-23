import tensorflow as tf

in_ = tf.placeholder(dtype=tf.float32, shape=(1, 16, 16, 3))
out_ = tf.nn.relu(in_)

# Ordered Graph Inputs
inputs = [in_]
# Ordered Graph Outputs
outputs = [out_]
