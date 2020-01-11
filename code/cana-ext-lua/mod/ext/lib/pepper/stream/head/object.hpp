#ifndef __PEPPER_STREAM_HEAD_OBJECT_H__
#define __PEPPER_STREAM_HEAD_OBJECT_H__

#include <pepper/maybe.hpp>

namespace pepper { namespace stream { namespace head {

  template <typename T> struct object
  {
    object() = default;
    virtual ~object() = default;

    virtual void forward(void) = 0;
    virtual pepper::maybe::object<T> access(void) const = 0;
  };

} } }

#endif
