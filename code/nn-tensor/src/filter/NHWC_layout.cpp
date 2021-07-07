#include "filter/NHWC_layout.h"

#include <cassert>

static uint64_t NHWC_offset(const filter::shape &shape, uint64_t n, uint64_t ch, uint64_t row, uint64_t col)
{
  return (((n * shape.height()) + row) * shape.width() + col) * shape.depth() + ch;
}

namespace filter
{

NHWC_layout::NHWC_layout() : layout{NHWC_offset}
{
  // DO NOTHING
}

} // namespace filter
