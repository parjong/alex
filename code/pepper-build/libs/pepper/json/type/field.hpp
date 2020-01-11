#ifndef __PEPPER_JSON_FIELD_H__
#define __PEPPER_JSON_FIELD_H__

#include <pepper/json/type/obj/value.hpp>

namespace pepper { namespace json { namespace type {

  template <typename T> class field
  {
    private:
      T _value;

    public:
      field(obj::value &obj, const std::string &name)
      {
        obj.add_field(name, _value);
      }      
      virtual ~field() = default;


    public:
      T &operator()(void) 
      { 
        return _value; 
      }
      
    public:
      const T&operator()(void) const
      {
        return _value;
      }
  };

} } }

#endif
