#include "pepper/json/util.hpp"
#include "pepper/json/value/object.hpp"
#include "pepper/json/archive.hpp"

#include <json/json.h>

namespace pepper { namespace json {

  void operator>>(const Json::Value &json, object &obj)
  {
    archive<object>::load(json, obj);
  }

  void operator<<(Json::Value &json, const object &obj)
  {
    archive<object>::dump(json, obj);       
  }

  std::istream &operator>>(std::istream &is, object &obj)
  {
    Json::Value json;
    Json::Reader reader;

    reader.parse(is, json);

    archive<object>::load(json, obj);

    return is;
  }

  std::ostream &operator<<(std::ostream &os, const object &obj)
  {
    Json::Value json;

    archive<object>::dump(json, obj);    

    os << json.toStyledString();

    return os;
  }

} }
