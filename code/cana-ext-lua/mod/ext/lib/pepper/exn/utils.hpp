#ifndef __PEPPER_EXN_UTILS_H__
#define __PEPPER_EXN_UTILS_H__

#include <pepper/exn/object.hpp>

namespace pepper { namespace exn {

  template <typename... Args> void raise(const Args&... args)
  {
    throw typed_object<Args...>{ args... };
  }

  template <typename... Args> void raise_if(bool b, const Args&... args)
  {
    if ( b )
      throw typed_object<Args...>{ args... };
  }

  template <typename... Args> void raise_unless(bool b, const Args&... args)
  {
    if ( !b )
      throw typed_object<Args...>{ args... };
  }

} } 

#endif
