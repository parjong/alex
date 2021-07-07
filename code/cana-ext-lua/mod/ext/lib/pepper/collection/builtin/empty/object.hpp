#ifndef __PEPPER_COLLECTION_BUILTIN_EMPTY_OBJECT_H__
#define __PEPPER_COLLECTION_BUILTIN_EMPTY_OBJECT_H__

#include <pepper/collection/builtin/empty/data/object.hpp>
#include <pepper/collection/object.hpp>

namespace pepper { namespace collection { namespace builtin { namespace empty {

  template <typename T> struct object : public pepper::collection::object<T>
  {
    object() = default;
    virtual ~object() = default;

    virtual pepper::collection::data::bean<T> collection(void) const
    {
      return pepper::mem::shared::make<pepper::collection::data::object<T>, empty::data::object<T>>();
    }
  };

} } } }

#endif
