#ifndef __FILTER_READABLE_H__
#define __FILTER_READABLE_H__

#include <cstdint>

namespace filter
{

template<typename T> struct readable
{
  virtual ~readable() = default;

  virtual T at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) const = 0;
};

} // namespace filter

#endif // __FILTER_READABLE_H__
