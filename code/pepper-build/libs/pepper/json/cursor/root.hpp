#ifndef __PEPPER_JSON_CURSOR_ROOT_H__
#define __PEPPER_JSON_CURSOR_ROOT_H__

#include <pepper/json/cursor/base.hpp>

namespace pepper { namespace json { namespace cursor {

  class root : public base
  {
    private:
      Json::Value &_root;

    public:
      root(Json::Value &r); 

    public:
      virtual Json::Value &get_writer(void) const;     
      virtual const Json::Value &get_reader(void) const; 
  };

} } } 

#endif
