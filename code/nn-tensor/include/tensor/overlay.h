#ifndef __TENSOR_OVERLAY_H__
#define __TENSOR_OVERLAY_H__

#include "tensor/object.h"

namespace tensor
{

template<typename T> class overlay final : public object<T>
{
public:
  overlay(const tensor::shape &shape, const tensor::layout &layout, T *data)
      : object<T>{shape, layout}, _data{data}
  {
    // DO NOTHING
  }

public:
  overlay(const overlay &) = default;
  overlay(overlay &&) = default;

public:
  T *data(void) override { return _data; }
  const T *data(void) const override { return _data; }

private:
  T * _data;
};

} // namespace tensor

namespace tensor
{

template<typename Layout> struct overlay_factory
{
  template<typename T> static overlay<T> make(const tensor::shape &shape, T *data)
  {
    return overlay<T>{shape, Layout{}, data};
  }
};

} // namespace tensor

#endif // __TENSOR_OVERLAY_H__
