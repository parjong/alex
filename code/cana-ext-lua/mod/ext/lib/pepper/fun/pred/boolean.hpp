#ifndef __PEPPER_FUN_PRED_BOOLEAN_H__
#define __PEPPER_FUN_PRED_BOOLEAN_H__

#include <functional>

namespace pepper { namespace fun { namespace pred {

  template <typename T> std::function<bool (const T &)> neg(const std::function<bool (const T &)> &p)
  {
    return [&] (const T &v) {
      return !p( v );
    };
  }

} } }

#endif
