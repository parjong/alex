#include <pepper/jsoncpp/path/named/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace named {

  accessor::accessor(const path::object &prev, const std::string &name) : _prev{prev}
  {
    _name = name;
  }

  Json::Value &accessor::access(Json::Value &value)
  {
    return _prev.access(value)[_name];
  }

  const Json::Value &accessor::access(const Json::Value &value) const
  {
    return _prev.access(value)[_name];
  }

} } } }
