#ifndef __TENSOR_SHAPE_H__
#define __TENSOR_SHAPE_H__

#include "tensor/shaped.h"

#include <vector>
#include <initializer_list>
#include <cstdint>

namespace tensor
{

class shape final : public shaped<uint64_t>
{
public:
  shape() = default;
  shape(std::initializer_list<uint64_t> l);

public:
  uint32_t rank(void) const override;

public:
  shape &resize(uint32_t size);

public:
  uint64_t &dim(uint32_t axis) override;
  uint64_t dim(uint32_t axis) const override;

private:
  std::vector<uint64_t> _dims;
};

} // namespace tensor

#endif // __TENSOR_SHAPE_H__
