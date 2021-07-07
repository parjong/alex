#ifndef __FEATURE_SHAPE_H__
#define __FEATURE_SHAPE_H__

#include <cstdint>

namespace feature
{

class shape
{
public:
  shape() = default;

public:
  shape(uint64_t C, uint64_t H, uint64_t W) : _depth{C}, _height{H}, _width{W}
  {
    // DO NOTHING
  }

public:
  uint64_t depth(void) const { return _depth; }
  uint64_t height(void) const { return _height; }
  uint64_t width(void) const { return _width; }

private:
  uint64_t _depth;
  uint64_t _height;
  uint64_t _width;
};

} // namespace feature

static inline uint32_t num_elements(const feature::shape &shape)
{
  return shape.depth() * shape.height() * shape.width();
}

#endif // __FEATURE_SHAPE_H__
