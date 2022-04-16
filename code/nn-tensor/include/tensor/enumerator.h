#ifndef __TENSOR_ENUMERATOR_H__
#define __TENSOR_ENUMERATOR_H__

#include "tensor/shape.h"
#include "tensor/index.h"

namespace tensor
{

class enumerator
{
public:
  explicit enumerator(const shape &s);

public:
  bool valid(void) const;
  const index &curr(void) const { return _index; }

public:
  enumerator &next(void);

private:
  const shape _shape;

private:
  uint32_t _cursor;
  index _index;
};

} // namespace tensor

#endif // __TENSOR_ENUMERATOR_H__
