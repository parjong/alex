import tensorflow as tf

lhs_ = tf.placeholder(dtype=tf.float32, shape=(1, 16, 16, 3))
rhs_ = tf.placeholder(dtype=tf.float32, shape=(1, 16, 16, 3))
out_ = tf.math.add(lhs_, rhs_)

# Ordered Graph Inputs
inputs = [lhs_, rhs_]
# Ordered Graph Outputs
outputs = [out_]
