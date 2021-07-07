#ifndef __PEPPER_COLLECTION_OBJECT_H__
#define __PEPPER_COLLECTION_OBJECT_H__

#include <pepper/collection/data.hpp>
#include <pepper/collection/block.hpp>
#include <pepper/stream.hpp>

namespace pepper { namespace collection {

  template <typename T> struct object
  {
    object() = default;
    virtual ~object() = default;
  
    virtual collection::data::bean<T> collection(void) const = 0;

    stream::data::bean<T> stream(void) const
    {
      return collection().stream();
    }

    int count(void) const
    {
      int ret = 0;

      auto cur = collection().cursor();

      while (cur.access().filled())
      {
        ++ret; cur.forward();
      }

      return ret;
    }
  };

  template <typename T> block::foreach<T> foreach(const object<T> &obj)
  {
    return block::foreach<T>{obj.collection()};
  }

  template <typename T> block::forall<T> forall(const object<T> &obj)
  {
    return block::forall<T>{obj.collection()};
  }

} }

#endif
