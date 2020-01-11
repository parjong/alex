#ifndef __PEPPER_JSON_TYPE_STR_FIELD_H__
#define __PEPPER_JSON_TYPE_STR_FIELD_H__

#include <pepper/json/type/field.hpp>
#include <pepper/json/type/str/value.hpp>

namespace pepper { namespace json { namespace type { namespace str {

  class field : public type::field<str::value>
  {
    public:
      field(obj::value &obj, const std::string &name);
      virtual ~field() = default;
  };

} } } }

#endif
