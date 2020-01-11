#ifndef __PEPPER_FILTER_UNIT_H__
#define __PEPPER_FILTER_UNIT_H__

#include <pepper/filter/action.hpp>

namespace pepper { namespace filter {

  template <typename T> struct unit 
  {
    unit() = default;
    virtual ~unit() = default;

    virtual filter::action check(const T &value) const = 0;
  };

} }

#endif
