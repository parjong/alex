#ifndef __PEPPER_FUN_PRED_NUMERIC_H__
#define __PEPPER_FUN_PRED_NUMERIC_H__

namespace pepper { namespace fun { namespace pred {

  template <typename T> std::function<bool (const T &)> gt(const T &rhs)
  {
    return [rhs] (const T &lhs) {
      return lhs > rhs;
    };
  }

  template <typename T> std::function<bool (const T &)> ge(const T &rhs)
  {
    return [rhs] (const T &lhs) {
      return lhs >= rhs;
    };
  }

} } }

#endif
