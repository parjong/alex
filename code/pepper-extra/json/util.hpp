#ifndef __PEPPER_JSON_UTIL_H__
#define __PEPPER_JSON_UTIL_H__

#include "pepper/json/json.forward.hpp"
#include "pepper/json/value/object.forward.hpp"
#include "pepper/json/value/dict.hpp"

#include "pepper/json/archive.hpp"

#include <iostream>

namespace pepper { namespace json {
  
  void operator>>(const Json::Value &value, object &m);

  template <typename T> void operator>>(const Json::Value &json, dict<T> &dict)
  {
    archive<json::dict<T>>::load(json, dict);
  }

  void operator<<(Json::Value &value, const object &m);

  std::istream &operator>>(std::istream &is, object &m);
  std::ostream &operator<<(std::ostream &os, const object &m);  

  template <typename T> void describe(std::ostream &os)
  {
    Json::Value value;
    pepper::json::archive<T>::desc(value);
    std::cout << value << std::endl;
  }

} }

#endif
