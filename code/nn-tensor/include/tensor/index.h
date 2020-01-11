#ifndef __TENSOR_INDEX_H__
#define __TENSOR_INDEX_H__

#include <vector>
#include <initializer_list>

#include <cstdint>

namespace tensor
{

class index
{
public:
  index() = default;
  index(std::initializer_list<uint64_t> l);

public:
  uint32_t rank(void) const;

public:
  index &resize(uint32_t size);

public:
  uint64_t &at(uint32_t axis);
  const uint64_t &at(uint32_t axis) const;

private:
  std::vector<uint64_t> _indices;
};

} // namespace tensor

#endif // __TENSOR_INDEX_H__
