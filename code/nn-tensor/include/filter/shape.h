#ifndef __FILTER_SHAPE_H__
#define __FILTER_SHAPE_H__

#include <vector>
#include <initializer_list>

#include <cstdint>

namespace filter
{

class shape
{
public:
  shape() = default;
  shape(uint64_t N, uint64_t C, uint64_t H, uint64_t W)
      : _count{N}, _depth{C}, _height{H}, _width{W}
  {
    // DO NOTHING
  }

public:
  uint64_t count(void) const { return _count; }
  uint64_t depth(void) const { return _depth; }
  uint64_t height(void) const { return _height; }
  uint64_t width(void) const { return _width; }

private:
  uint64_t _count;
  uint64_t _depth;
  uint64_t _height;
  uint64_t _width;
};

static inline uint64_t num_elements(const filter::shape &shape)
{
  return shape.count() * shape.depth() * shape.height() * shape.width();
}

} // namespace filter

#endif // __FILTER_SHAPE_H__
