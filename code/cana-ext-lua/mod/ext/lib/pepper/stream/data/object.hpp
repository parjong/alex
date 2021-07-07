#ifndef __PEPPER_STREAM_DATA_OBJECT_H__
#define __PEPPER_STREAM_DATA_OBJECT_H__

#include <pepper/stream/head.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace stream { namespace data {

  template <typename T> struct object
  {
    object() = default;
    virtual ~object() = default;

    virtual stream::head::bean<T> head(void) const = 0;
  };

} } }

#endif
