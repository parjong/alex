#include <pepper/jsoncpp/image/value/accessor.hpp>
#include <pepper/jsoncpp/path.hpp>

#include <jsoncpp/json/json.h>

namespace pepper { namespace jsoncpp { namespace image { namespace value {

  accessor::accessor(std::istream &is)
  {
    is >> _value;
  }

  const Json::Value &accessor::value(void) const
  {
    return _value;
  }

} } } }
