#ifndef __FILTER_VIEW_H__
#define __FILTER_VIEW_H__

#include "filter/shape.h"
#include "filter/readable.h"
#include "filter/accessible.h"

namespace filter
{

template<typename T> struct view : public readable<T>, public accessible<T>
{
  virtual ~view() = default;

  virtual const filter::shape &shape(void) const = 0;
};

} // namespace filter

#endif // __FILTER_VIEW_H__
