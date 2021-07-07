spec = gef_spec()

model = spec.get_model()

model.get_input_signature()
model.get_ouput_signature()

# get_input_signature() returns a list of TensorSignature
#
# Each TensorSignature has the following attributes:
# kind Q8 or Q16
# shape
# scale
# zero_point (if kind ==  Q16)

input_count = len(model.get_input_signature())

assert input_count == 1

spec.generate_recipe() # String
spec.generate_input(0) # NDArray
spec.generate_input_list() # NDArray List
