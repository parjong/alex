#include <pepper/jsoncpp/image/cref/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace image { namespace cref {

  accessor::accessor(const Json::Value &ref) : _ref(ref)
  {
    // DO NOTHING
  }

  const Json::Value &accessor::value(void) const
  {
    return _ref;
  }

} } } }
