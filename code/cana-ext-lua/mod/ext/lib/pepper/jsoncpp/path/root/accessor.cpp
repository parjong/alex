#include <pepper/jsoncpp/path/root/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace root {

  Json::Value &accessor::access(Json::Value &value)
  {
    return value;
  }

  const Json::Value &accessor::access(const Json::Value &value) const
  {
    return value;
  }

} } } }
