#include <pepper/json/cursor/indexed/accessor.hpp>

namespace pepper { namespace json { namespace cursor { namespace indexed {

  accessor::accessor(const cursor::object &cur, int ind) : _cur{cur}
  {
    _ind = ind;
  }

  Json::Value &accessor::get_writer(void) const 
  { 
    return _cur.get_writer()[_ind]; 
  }

  const Json::Value &accessor::get_reader(void) const 
  { 
    return _cur.get_reader()[_ind]; 
  }

} } } }
