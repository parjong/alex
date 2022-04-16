#ifndef __FILTER_OVERLAY_H__
#define __FILTER_OVERLAY_H__

#include <filter/view.h>
#include <filter/view_impl.h>

namespace filter
{

template<typename T, typename It> class overlay final : public view<T>
{
public:
  overlay(const filter::shape &shape, const layout &layout, It it)
      : _impl{shape, layout}, _it{it}
  {
  }

public:
  const filter::shape &shape(void) const override { return _impl.shape(); }

public:
  T &at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) override
  {
    return _impl.at(_it, n, ch, row, col);
  }

  T at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) const override
  {
    return _impl.at(_it, n, ch, row, col);
  }

private:
  view_impl<T> _impl;

private:
  It _it;
};

template<typename T, typename LayoutImpl> struct overlay_factory
{
  template<typename It>
  static overlay<T, It> make(const filter::shape &shape, It it)
  {
    return overlay<T, It>{shape, LayoutImpl{}, it};
  }
};

} // namespace filter

#endif // __FILTER_OVERLAY_H__
