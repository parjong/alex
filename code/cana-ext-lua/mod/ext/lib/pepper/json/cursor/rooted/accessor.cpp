#include <pepper/json/cursor/rooted/accessor.hpp>

namespace pepper { namespace json { namespace cursor { namespace rooted {

  accessor::accessor(Json::Value &r)
    : _root(r)
  {
    // DO NOTHINg
  }

  Json::Value &accessor::get_writer(void) const
  {
    return _root;
  }

  const Json::Value &accessor::get_reader(void) const
  {
    return _root;
  }

} } } }
