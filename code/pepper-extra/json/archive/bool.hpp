#ifndef __PEPPER_JSON_ARCHIVE_BOOL_H__
#define __PEPPER_JSON_ARCHIVE_BOOL_H__

#include "pepper/json/json.forward.hpp"
#include "pepper/json/archive/base.hpp"

namespace pepper { namespace json {

  template <> struct archive<bool>
  {
    static void load(const Json::Value &json, bool &obj);
    static void dump(Json::Value &json, const bool &obj);
    static void desc(Json::Value &json);
  };

} }

#endif
