#include <pepper/json/cursor/named/accessor.hpp>

namespace pepper { namespace json { namespace cursor { namespace named {

  accessor::accessor(const cursor::object &cur, const std::string &tag) : _cur{cur}
  {
    _tag = tag;
  }

  Json::Value &accessor::get_writer(void) const 
  { 
    return _cur.get_writer()[_tag]; 
  }      

  const Json::Value &accessor::get_reader(void) const 
  { 
    return _cur.get_reader()[_tag]; 
  }      

} } } }
