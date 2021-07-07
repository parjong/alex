#ifndef __PEPPER_MEMORY_SPAN_H__
#define __PEPPER_MEMORY_SPAN_H__

#include <cstdint>

namespace pepper
{

template<typename T> class span
{
public:
  span() : _data{nullptr}, _size{0}
  {
    // DO NOTHING
  }

public:
  span(T *data, uint64_t size) : _data{data}, _size{size}
  {
    // DO NOTHING
  }

public:
  ~span() = default;

public:
  uint64_t size(void) const { return _size; }

public:
  T &at(uint64_t offset) { return _data[offset]; }
  const T &at(uint64_t offset) const { return _data[offset]; }

public:
  T &operator[](uint64_t offset) { return at(offset); }
  const T &operator[](uint64_t offset) const { return at(offset); }

private:
  T * _data;
  uint64_t _size;
};

} // namespace pepper

#endif // __PEPPER_MEMORY_SPAN_H__
