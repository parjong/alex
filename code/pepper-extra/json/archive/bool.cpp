#include "pepper/json/archive/bool.hpp"

#include <json/json.h>

namespace pepper { namespace json {

  void archive<bool>::load(const Json::Value &json, bool &obj)
  {
    obj = json.asBool();
  }

  void archive<bool>::dump(Json::Value &json, const bool &obj)    
  {
    json = obj;
  }

  void archive<bool>::desc(Json::Value &json)
  {
    json = true;
    json.setComment("// boolean value", Json::commentAfterOnSameLine);
  }

} }

