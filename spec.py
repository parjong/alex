# Let's implement https://github.com/Samsung/ONE/blob/master/res/TensorFlowLiteRecipes/Conv2D_U8_000/test.recipe
#
# The below specification includes the followings additionally
# - How to generate an input
# - How to match the output
import numpy as np

with Q8Tensor('ifm') with t:
    t.shape = (1, 3, 3, 2)
    # Use 'SCALE' and 'ZERO_POINT' by default
    # min/max will be derived from scale and zero_point
    t.scale = 0.004
    t.zero_point = 0
"""
operand {
  name: "ifm"
  type: UINT8
  shape { dim: 1 dim: 3 dim: 3 dim: 2}
  quant { min: 0 max: 1 scale: 0.004 zero_point: 0 }
"""

with Q8NCFilterConst('ker') with c:
    f64_value = np.random.rand(1, 1, 1, 2) * 255
    c.value = f64_value.astype(np.uint8) # Gaussian
    # TODO Allow users to use 'MIN/MAX'
    c.scale = 0.039215686
    c.zero_point = 102

# The above block will generate the following recipe fragment
"""
operand {
  name: "ker"
  type: UINT8
  shape { dim: 1 dim: 1 dim: 1 dim: 2 }
  quant { min: -4 max: 6 scale: 0.039215686 zero_point: 102 }
  filler { tag: "explicit" arg: "..." arg: "..." }
}
"""
# 'Q8...' helper set 'type' as UINT8
# 'value' field contributes to 'shape' and 'fillter'
# '...Const' helper inserts 'filler' automatically

# The code below allow users to generate a channel-wise quantized filter
# with CQ8NCFilterConst('ker') with c:
#     c.value = ...
#     c.scale = [ ... ]
#     c.zero_point = [ ... ]

with Q32BiasConst('bias') with c:
    f64_value = np.random.rand(2) * 255
    c.value = f64_value.astype(np.uint8)
    c.scale = 0.00015686276310589164
    c.zero_point = 0
"""
operand {
  name: "bias"
  type: INT32
  shape { dim: 1 }
  filler {
    tag: "gaussian"
    arg: "0"
    arg: "1024"
  }
  quant { scale: 0.00015686276310589164 zero_point: 0 }
}
"""

with Q8Tensor('ofm') as t:
	t.shape = (1, 3, 3, 1)
	t.scale = 0.039215686
	t.zero_point = 102
"""
operand {
  name: "ofm"
  type: UINT8
  shape { dim: 1 dim: 3 dim: 3 dim: 1 }
  quant { min: -4 max: 6 scale: 0.039215686 zero_point: 102 }
}
"""

with opertion('CONV_2D') as o:
	# For conv2d_options
	o.padding = 'VALID'
	o.stride_w = 1
	o.stride_h = 1

	# input:
	o.add_input('ifm')
	o.add_input('ker')
	o.add_input('bias')

	# output:
	o.add_output('ofm')
"""
operation {
  type: "Conv2D"
  conv2d_options {
    padding: VALID
    stride_w: 1
    stride_h: 1
  }
  input: "ifm"
  input: "ker"
  input: "bias"
  output: "ofm"
}
"""

with model_input(ifm) as mi:
  mi.follow_uniform_distrib(min=0, max=255)

with model_output(ofm) as mo:
  mo.use_exact_match()
