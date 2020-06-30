# encaf

NN Compiler Assesement Framework


```
Model

Attributes
----------
format: Format
input_signature: list[signature]
output_signature: list[signature]

Methods
-------
input: index -> signature
output: index -> signature
infer: list[np.array] -> list[np.array]
```
