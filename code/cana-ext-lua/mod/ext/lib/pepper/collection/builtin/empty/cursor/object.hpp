#ifndef __PEPPER_COLLECTION_BUILTIN_EMPTY_CURSOR_OBJECT_H__
#define __PEPPER_COLLECTION_BUILTIN_EMPTY_CURSOR_OBJECT_H__

#include <pepper/collection/cursor.hpp>

namespace pepper { namespace collection { namespace builtin { namespace empty { namespace cursor {

  template <typename T> struct object : public pepper::collection::cursor::object<T>
  {
    object() = default;
    virtual ~object() = default;

    virtual maybe::object<T> access(unsigned off) const
    {
      return pepper::maybe::none<T>();
    }

    virtual void forward(unsigned off)
    {
      return;
    }
  };

} } } } }

#endif
