#ifndef __PEPPER_JSON_CURSOR_OBJECT_H__
#define __PEPPER_JSON_CURSOR_OBJECT_H__

#include <pepper/json/cursor/accessor.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace json { namespace cursor {

  class object
  {
    private:
      std::shared_ptr<cursor::accessor> _accessor;

    public:
      object(const object &o) 
      {
        _accessor = o._accessor;
      }

      object(const std::shared_ptr<cursor::accessor> &accessor)
      {
        _accessor = accessor;
      }
    
    public:
      Json::Value &get_writer(void) const
      {
        return _accessor->get_writer();
      }
      
      const Json::Value &get_reader(void) const
      {
        return _accessor->get_reader();
      }
  };

} } }

#endif
