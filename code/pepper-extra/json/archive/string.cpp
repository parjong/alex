#include "pepper/json/archive/string.hpp"

#include <json/json.h>

namespace pepper { namespace json {

  void archive<std::string>::load(const Json::Value &json, std::string &obj)
  {
    obj = json.asString();
  }

  void archive<std::string>::dump(Json::Value &json, const std::string &obj)    
  {
    json = obj;
  }

  void archive<std::string>::desc(Json::Value &json)    
  {
    json = "string value";
  }

} }

