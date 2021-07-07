#ifndef __FILTER_VIEW_IMPL_H__
#define __FILTER_VIEW_IMPL_H__

#include "filter/shape.h"
#include "filter/layout.h"

namespace filter
{

template<typename T> class view_impl
{
public:
  view_impl(const filter::shape &shape, const layout &layout)
      : _shape{shape}, _layout{layout}
  {
    // DO NOTHING
  }

public:
  const filter::shape &shape(void) const { return _shape; }

public:
  template<typename InputIt>
  T &at(InputIt it, uint32_t n, uint32_t ch, uint32_t row, uint32_t col)
  {
    return *(it + _layout.offset(_shape, n, ch, row, col));
  }

  template<typename InputIt>
  T at(InputIt it, uint32_t n, uint32_t ch, uint32_t row, uint32_t col) const
  {
    return *(it + _layout.offset(_shape, n, ch, row, col));
  }

private:
  const filter::shape _shape;
  const layout _layout;
};

} // namespace filter

#endif // __FILTER_VIEW_IMPL_H__
