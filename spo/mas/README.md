## What is mas for?

_mas_ makes it simple to analyze neural network models.

**NOTE** _mas_ is an abbreviation of **m**odel **a**nalysis **s**cript.

## Advanced: Roofline Modeling with a .tflite model

**NOTE** Please initialize your local environment first

Type the following commands to download ``Mobilenet_V1_1.0_224`` served in
[tensorflow site](https://www.tensorflow.org/lite/guide/hosted_models):
```shell
WS=$(mktemp -d) # You may use your own directory

wget -O "$WS/mobilenet_v1_1.0_224.tgz" \
  https://storage.googleapis.com/download.tensorflow.org/models/mobilenet_v1_2018_02_22/mobilenet_v1_1.0_224.tgz

tar -xvzf "$WS/mobilenet_v1_1.0_224.tgz" -C $WS
```

**NOTE** Skip this step if you have your own .tflite model to analyze

Set ``MODEL_PATH``:
```
MODEL_PATH="$WS/mobilenet_v1_1.0_224.tflite"
```

**NOTE** Use your own .tflite model if you didn't download ``Mobilenet_V1_1.0_224``

```
./dev analyze-tflite -m "$MODEL_PATH" \
  example/roofline/compute.W.TFL.mas \
  example/roofline/compute.Q.mas \
  example/roofline/print.mas
```
