#ifndef __TENSOR_READABLE_H__
#define __TENSOR_READABLE_H__

#include "tensor/index.h"

namespace tensor
{

template<typename T> struct readable
{
  virtual ~readable() = default;

  virtual T at(const index &) const = 0;
};

} // namespace tensor

#endif // __TENSOR_READABLE_H__
