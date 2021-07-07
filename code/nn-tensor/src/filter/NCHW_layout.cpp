#include "filter/NCHW_layout.h"

#include <cassert>

static uint64_t NCHW_offset(const filter::shape &shape, uint64_t n, uint64_t ch, uint64_t row, uint64_t col)
{
  return (((n * shape.depth()) + ch) * shape.height() + row) * shape.width() + col;
}

namespace filter
{

NCHW_layout::NCHW_layout() : layout{NCHW_offset}
{
  // DO NOTHING
}

} // namespace filter
