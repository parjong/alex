#ifndef __PEPPER_FMT_UTILS_H__
#define __PEPPER_FMT_UTILS_H__

#include <pepper/fmt/value.hpp>

namespace pepper { namespace fmt {

  template <typename... Args> value<Args...> make(const Args&... args)
  {
    return value<Args...>{args...};
  }

} }

#endif
