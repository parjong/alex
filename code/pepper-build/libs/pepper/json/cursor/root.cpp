#include <pepper/json/cursor/root.hpp>

namespace pepper { namespace json { namespace cursor {

  root::root(Json::Value &r) 
    : _root(r) 
  {
    // DO NOTHINg
  }

  Json::Value &root::get_writer(void) const 
  { 
    return _root;  
  }

  const Json::Value &root::get_reader(void) const 
  { 
    return _root;  
  } 

} } }
