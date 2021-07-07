#ifndef __TENSOR_SHAPED_H__
#define __TENSOR_SHAPED_H__

#include <cstdint>

namespace tensor
{

template<typename T> struct shaped
{
  virtual ~shaped() = default;

  virtual uint32_t rank(void) const = 0;

  virtual T &dim(uint32_t axis) = 0;
  virtual T dim(uint32_t axis) const = 0;
};

} // namespace tensor

#endif // __TENSOR_SHAPED_H__
