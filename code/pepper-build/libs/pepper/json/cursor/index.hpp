#ifndef __PEPPER_JSON_CURSOR_INDEX_H__
#define __PEPPER_JSON_CURSOR_INDEX_H__

#include <pepper/json/cursor/base.hpp>

namespace pepper { namespace json { namespace cursor {

  class index : public base
  {
    private:
      const cursor::base &_cur;
      int _ind;

    public:
      index(const cursor::base &cur, int ind)
        : _cur(cur), _ind(ind)
      {
      }

    public:
      virtual Json::Value &get_writer(void) const 
      { 
        return _cur.get_writer()[_ind]; 
      }
      
      virtual const Json::Value &get_reader(void) const 
      { 
        return _cur.get_reader()[_ind]; 
      }
  };

} } }

#endif
