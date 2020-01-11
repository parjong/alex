#ifndef __PEPPER_JSON_CURSOR_FIELD_H__
#define __PEPPER_JSON_CURSOR_FIELD_H__

#include <pepper/json/cursor/base.hpp>

namespace pepper { namespace json { namespace cursor {

  class field : public base
  {
    private:
      const cursor::base &_cur;
      const std::string &_tag;

    public:
      field(const cursor::base &cur, const std::string &tag)
        : _cur(cur), _tag(tag)
      {
        // DO NOTHINg
      }

    public:
      virtual Json::Value &get_writer(void) const 
      { 
        return _cur.get_writer()[_tag]; 
      }      
      
    public:
      virtual const Json::Value &get_reader(void) const 
      { 
        return _cur.get_reader()[_tag]; 
      }      
  };      

} } }

#endif
