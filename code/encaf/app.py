import warnings

# To suppress FutureWarning from numpy
warnings.simplefilter(action='ignore', category=FutureWarning)

import logging

import click
import numpy as np

import encaf.tflite

@click.command()
@click.option('--tflite-model')
def app(tflite_model):
    console = logging.StreamHandler()
    console.setLevel(logging.INFO)

    # Add console handler to the root logger
    logging.getLogger('').addHandler(console)

    with open(tflite_model, 'rb') as f:
        tflite_model = encaf.tflite.Model(f.read())

    print(tflite_model.input_signature[0].dtype)
    print(tflite_model.input_signature[0].shape)
    print(tflite_model.input_signature[0].index)

    print(tflite_model.output_signature[0].dtype)
    print(tflite_model.output_signature[0].shape)
    print(tflite_model.output_signature[0].index)

    input_tuple = [np.random.randint(0, high=255, size=(1, 224, 224, 3), dtype='u1')]
    output_tuple = tflite_model.infer(input_tuple)
    print(output_tuple)
    print(output_tuple[0].argmax())

    # TODO Implement this
    print('Hello, World from App')

    pass

app()
