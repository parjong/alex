#ifndef __FILTER_ACCESSIBLE_H__
#define __FILTER_ACCESSIBLE_H__

#include <cstdint>

namespace filter
{

template<typename T> struct accessible
{
  virtual ~accessible() = default;

  virtual T &at(uint64_t n, uint64_t ch, uint64_t row, uint64_t col) = 0;
};

} // namespace filter

#endif // __FILTER_ACCESSIBLE_H__
