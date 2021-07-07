#ifndef __NNI_CORE_TENSOR_ACCESSOR_H__
#define __NNI_CORE_TENSOR_ACCESSOR_H__

#include <tensor/index.h>

template<typename T> struct TensorAccessor
{
  virtual ~TensorAccessor() = default;

  virtual T at(const tensor::index &) const = 0;
  virtual T &at(const tensor::index &) = 0;
};

#endif // __NNI_CORE_TENSOR_ACCESSOR_H__
