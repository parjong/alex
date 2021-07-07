#ifndef __NNI_CORE_TENSOR_REF_H__
#define __NNI_CORE_TENSOR_REF_H__

#include "nni/core/TensorAccessor.h"

#include <memory>

template<typename T> class TensorRef
{
public:
  TensorRef(std::unique_ptr<TensorAccessor<T>> &&acc) : _acc{std::move(acc)}
  {
    // DO NOTHING
  }

public:
  T at(const tensor::index &index) const { return _acc->at(index); }
  T &at(const tensor::index &index) { return _acc->at(index); }

private:
  std::unique_ptr<TensorAccessor<T>> _acc;
};

#endif // __NNI_CORE_TENSOR_REF_H__
