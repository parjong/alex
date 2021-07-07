#ifndef __PEPPER_STREAM_OBJECT_H__
#define __PEPPER_STREAM_OBJECT_H__

#include <pepper/stream/data.hpp>

namespace pepper { namespace stream {

  template <typename T> struct object
  {
    object() = default;
    virtual ~object() = default;
  
    virtual stream::data::bean<T> stream(void) const = 0;
  };

} }

#endif
