#ifndef __PEPPER_COLLECTION_BUILTIN_EMPTY_DATA_OBJECT_H__
#define __PEPPER_COLLECTION_BUILTIN_EMPTY_DATA_OBJECT_H__

#include <pepper/collection/builtin/empty/cursor/object.hpp>
#include <pepper/collection/data/object.hpp>

namespace pepper { namespace collection { namespace builtin { namespace empty { namespace data {

  template <typename T> struct object : public pepper::collection::data::object<T>
  {
    object() = default;
    virtual ~object() = default;

    virtual pepper::collection::cursor::bean<T> cursor(void) const
    {
      return pepper::mem::shared::make<pepper::collection::cursor::object<T>, empty::cursor::object<T>>();
    }
  };

} } } } }

#endif
