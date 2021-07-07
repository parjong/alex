#ifndef __TENSOR_LAYOUT_H__
#define __TENSOR_LAYOUT_H__

#include "tensor/shape.h"
#include "tensor/index.h"

namespace tensor
{

class layout
{
public:
  using fn = uint64_t (*)(const shape &, const index &);

public:
  layout() = default;

public:
  layout(layout::fn fn) : _fn{fn}
  {
    // DO NOTHING
  }

public:
  layout(const layout &) = default;
  layout(layout &&) = default;

public:
  uint64_t offset(const shape &s, const index &i) const
  {
    return _fn(s, i);
  }

private:
  layout::fn const _fn;
};

} // namespace tensor

#endif // __TENSOR_LAYOUT_H__
