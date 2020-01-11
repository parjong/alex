#include "tensor/lexical_layout.h"

#include <cassert>

static uint64_t lexical_offset(const tensor::shape &shape, const tensor::index &index)
{
  assert(shape.rank() == index.rank());
  assert(shape.rank() > 0);

  uint64_t res = index.at(0);

  for (uint32_t axis = 1; axis < shape.rank(); ++axis)
  {
    res *= shape.dim(axis);
    res += index.at(axis);
  }

  return res;
}

namespace tensor
{

lexical_layout::lexical_layout() : layout{lexical_offset}
{
  // DO NOTHING
}

const lexical_layout &lexical_layout::get(void)
{
  static const lexical_layout l;
  return l;
}

} // namespace tensor
