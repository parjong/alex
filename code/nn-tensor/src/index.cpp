#include "tensor/index.h"

namespace tensor
{

index::index(std::initializer_list<uint64_t> l) : _indices{l}
{
  // DO NOTHING
}

uint32_t index::rank(void) const
{
  return _indices.size();
}

index &index::resize(uint32_t size)
{
  _indices.resize(size);
  return (*this);
}

uint64_t &index::at(uint32_t axis)
{
  return _indices.at(axis);
}

const uint64_t &index::at(uint32_t axis) const
{
  return _indices.at(axis);
}

} // namespace tensor
