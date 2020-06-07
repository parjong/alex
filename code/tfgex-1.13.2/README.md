# TensorFlow Graph Recipe Exporter

## Tutorial

```
$ tfgre-1.13.2 --output-prefix ... --script <path/to/tfges> <path/to/tfg>
```

- TensorFlow Graph Recipe (.tfg), and
- TensorFlow Graph Export Script (.tfges)

### How to create a GraphDef file

```
configure('pb')
export()
```

### How to create a text GraphDef file

```
configure('pbtxt')
export()
```

### How to create a TFLITE model

Here is the minimal export script to create a TFLITe model
```
configure('tflite')
export()
```

### How to create a quantized TFLITE model?

```python
configure('tflite')

set_inference_type('uint8')

# How to set
# - the range of all the inputs
# - the range of a speicific input
# - the range of all intermeidate tensors
set_range(input_index='0', scale=1.0, zero_point=8)

export()
```

## Reference

```
configure('tflite')

# Update 'inference_input_type'
input_type('float' or 'uint8') # float is default
# Update 'inference_type'
inference_type('float' or 'uint8') # float is default

input_range(index=0, scale=1.0, zero_point=8)
default_input_range(scale=1.0, zero_point=8)
default_inference_range(scale=1.0, zero_point=8)

export()
```
