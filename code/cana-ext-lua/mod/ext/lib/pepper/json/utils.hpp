#ifndef __PEPPER_JSON_UTILS_H__
#define __PEPPER_JSON_UTILS_H__

#include <pepper/json/type/value.hpp>

#include <iostream>

namespace pepper { namespace json { namespace type {

  std::ostream &operator<<(std::ostream &os, const pepper::json::type::value &o);
  std::istream &operator>>(std::istream &os, pepper::json::type::value &o);

} } }

#endif
