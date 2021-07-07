#include <pepper/jsoncpp/path/indexed/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace indexed {

  accessor::accessor(const path::object &prev, int offset) : _prev{prev}
  {
    _offset = offset;
  }

  Json::Value &accessor::access(Json::Value &value)
  {
    return _prev.access(value)[_offset];
  }

  const Json::Value &accessor::access(const Json::Value &value) const
  {
    return _prev.access(value)[_offset];
  }

} } } }
