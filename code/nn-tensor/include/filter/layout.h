#ifndef __FILTER_LAYOUT_H__
#define __FILTER_LAYOUT_H__

#include "filter/shape.h"

namespace filter
{

class layout
{
public:
  using fn = uint64_t (*)(const shape &, uint64_t n, uint64_t ch, uint64_t row, uint64_t col);

public:
  layout() = default;

public:
  layout(layout::fn fn) : _fn{fn}
  {
    // DO NOTHING
  }

public:
  layout(const layout &) = default;
  layout(layout &&) = default;

public:
  uint64_t offset(const shape &s, uint64_t n, uint64_t ch, uint64_t row, uint64_t col) const
  {
    return _fn(s, n, ch, row, col);
  }

private:
  layout::fn const _fn;
};

} // namespace filter

#endif // __FILTER_LAYOUT_H__
