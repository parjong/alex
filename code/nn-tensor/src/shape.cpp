#include "tensor/shape.h"

namespace tensor
{

shape::shape(std::initializer_list<uint64_t> l) : _dims{l}
{
  // DO NOTHING
}

uint32_t shape::rank(void) const
{
  return _dims.size();
}

shape &shape::resize(uint32_t size)
{
  _dims.resize(size);
  return (*this);
}

uint64_t &shape::dim(uint32_t axis)
{
  return _dims.at(axis);
}

uint64_t shape::dim(uint32_t axis) const
{
  return _dims.at(axis);
}

} // namespace tensor
