#ifndef __PEPPER_JSON_TYPE_MAP_FIELD_H__
#define __PEPPER_JSON_TYPE_MAP_FIELD_H__

#include <pepper/json/type/field.hpp>
#include <pepper/json/type/map/value.hpp>

namespace pepper { namespace json { namespace type { namespace map {

  template <typename T> 
    class field : public type::field<pepper::json::type::map::value<T>>
  {
    public:
      field(obj::value &obj, const std::string &name)
        : type::field<pepper::json::type::map::value<T>>{ obj, name }
      {
        // DO NOTHING
      }      
      virtual ~field() = default;
  };

} } } }

#endif
