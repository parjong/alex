#ifndef __PEPPER_JSON_FIELD_NUM_H__
#define __PEPPER_JSON_FIELD_NUM_H__

#include <pepper/json/type/field.hpp>
#include <pepper/json/type/num/value.hpp>

namespace pepper { namespace json { namespace type { namespace num {

  class field : public type::field<pepper::json::type::num::value>
  {
    public:
      field(obj::value &obj, const std::string &name);
      virtual ~field() = default;
  };

} } } }

#endif
