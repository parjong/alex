#ifndef __PEPPER_JSON_ARCHIVE_STRING_H__
#define __PEPPER_JSON_ARCHIVE_STRING_H__

#include "pepper/json/json.forward.hpp"
#include "pepper/json/archive/base.hpp"

#include <string>

namespace pepper { namespace json {

  template <> struct archive<std::string>
  {
    static void load(const Json::Value &json, std::string &obj);
    static void dump(Json::Value &json, const std::string &obj);
    static void desc(Json::Value &json);
  };

} }

#endif
