#include <pepper/json/utils.hpp>
#include <pepper/json/cursor/rooted/accessor.hpp>

#include <jsoncpp/json/json.h>

namespace pepper { namespace json { namespace type {
  
  std::ostream &operator<<(std::ostream &os, const pepper::json::type::value &o)
  {
    Json::Value json;

    json::cursor::object cur{
      pepper::mem::shared::make<json::cursor::accessor, json::cursor::rooted::accessor>(json)
    };

    o.dump_into(cur);

    os << json.toStyledString() << std::endl;

    return os;
  }

  std::istream &operator>>(std::istream &is, pepper::json::type::value &o)
  {
    Json::Value json;

    is >> json;

    json::cursor::object cur{
      pepper::mem::shared::make<json::cursor::accessor, json::cursor::rooted::accessor>(json)
    };

    o.load_from(cur);

    return is;
  }

} } }
