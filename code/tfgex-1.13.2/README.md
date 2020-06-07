# TensorFlow Graph Exporter

Given a TF Graph recipe (.tfg), _tfgex_ reads TF Graph Export Script (.tfges) and runs it.

## Tutorial

### Create a TensorFlow Lite model

The tutorial below shows how to create a TensorFlow Lite model from a TensorFlow Graph recipe.

```
$ cat > sample.tfg <<EOF
import tensorflow as tf

lhs_ = tf.placeholder(dtype=tf.float32, shape=(1, 16, 16, 3))
rhs_ = tf.placeholder(dtype=tf.float32, shape=(1, 16, 16, 3))
out_ = tf.math.add(lhs_, rhs_)

# The above TF Graph has two inputs.
inputs = [lhs_, rhs_]
# The above TF Graph has one output.
outputs = [out_]
EOF
```

```
$ cat > sample.tfges <<EOF
configure('tflite')
export()
EOF
```

```
$ ./alex pyapp install tfgex-1.13.2
$ ./alex pyapp install tfgex-1.13.2 --output-prefix sample --script sample.tfges sample.tfg
```
