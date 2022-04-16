#ifndef __TENSOR_OBJECT_H__
#define __TENSOR_OBJECT_H__

#include "tensor/shape.h"
#include "tensor/index.h"
#include "tensor/layout.h"
#include "tensor/readable.h"
#include <memory>

namespace tensor
{

template<typename T> class object : public readable<T>
{
public:
  object(const tensor::shape &shape, const tensor::layout &layout)
      : _shape{shape}, _layout{layout}
  {
    // DO NOTHING
  }

public:
  virtual ~object() = default;

public:
  virtual T *data(void) = 0;
  virtual const T *data(void) const = 0;

public:
  const tensor::shape &shape(void) const { return _shape; }

public:
  T at(const tensor::index &index) const override final
  {
    return *(data() + _layout.offset(_shape, index));
  }

public:
  T &at(const tensor::index &index)
  {
    return *(data() + _layout.offset(_shape, index));
  }

private:
  const tensor::shape _shape;
  const tensor::layout _layout;
};

} // namespace tensor

#endif // __TENSOR_VIEW_H__
