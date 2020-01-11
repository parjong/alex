#ifndef __FILTER_BUFFER_H__
#define __FILTER_BUFFER_H__

#include <filter/view.h>
#include <filter/view_impl.h>

#include <vector>

namespace filter
{

template<typename T> class buffer final : public view<T>
{
public:
  buffer(const filter::shape &shape, const layout &layout)
      : _impl{shape, layout}
  {
    _buffer.resize(num_elements(shape));
  }

public:
  const filter::shape &shape(void) const override { return _impl.shape(); }

public:
  T &at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) override
  {
    return _impl.at(_buffer.begin(), n, ch, row, col);
  }

  T at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) const override
  {
    return _impl.at(_buffer.begin(), n, ch, row, col);
  }

private:
  view_impl<T> _impl;
  std::vector<T> _buffer;
};

// Each layout should be default constructible
template<typename T, typename Layout> buffer<T> make_buffer(const filter::shape &shape)
{
  return buffer<T>{shape, Layout{}};
}

} // namespace filter

#endif // __FILTER_BUFFER_H__
