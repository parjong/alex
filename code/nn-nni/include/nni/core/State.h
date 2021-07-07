#ifndef __NNI_CORE_STATE_H__
#define __NNI_CORE_STATE_H__

#include "nni/core/TensorRef.h"

#include <string>

#include <tensor/shape.h>

struct State
{
  virtual ~State() = default;

  virtual uint32_t num_tensors(void) const = 0;

  virtual std::string name(uint32_t n) const = 0;
  virtual tensor::shape shape(uint32_t n) const = 0;

  virtual TensorRef<float> as_float(uint32_t n) = 0;
};

#endif // __NNI_CORE_STATE_H__
