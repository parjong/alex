#ifndef __PEPPER_COLLECTION_DATA_OBJECT_H__
#define __PEPPER_COLLECTION_DATA_OBJECT_H__

#include <pepper/collection/cursor.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace collection { namespace data {

  template <typename T> struct object : public stream::data::object<T>
  {
    object() = default;
    virtual ~object() = default;

    virtual collection::cursor::bean<T> cursor(void) const = 0;

    virtual stream::head::bean<T> head(void) const
    {
      return cursor().head();
    }
  };

} } }

#endif
