#ifndef __PEPPER_COLLECTION_BUILTIN_H__
#define __PEPPER_COLLECTION_BUILTIN_H__

#include <pepper/collection/builtin/empty.hpp>

namespace pepper { namespace collection {

  template <typename T> builtin::empty::object<T> empty(void)
  {
    return builtin::empty::object<T>{};
  }

} }

#endif
