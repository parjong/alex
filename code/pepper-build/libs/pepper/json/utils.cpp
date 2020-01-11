#include <pepper/json/utils.hpp>

#include <jsoncpp/json/json.h>

namespace pepper { namespace json { namespace type {
  
  std::ostream &operator<<(std::ostream &os, const pepper::json::type::value &o)
  {
    Json::Value json;

    pepper::json::cursor::root cur{ json };

    o.dump_into(cur);

    os << json.toStyledString() << std::endl;

    return os;
  }

  std::istream &operator>>(std::istream &is, pepper::json::type::value &o)
  {
    Json::Value json;

    is >> json;

    pepper::json::cursor::root cur{ json };

    o.load_from(cur);

    return is;
  }

} } }
