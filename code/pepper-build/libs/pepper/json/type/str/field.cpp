#include <pepper/json/type/str/field.hpp>

namespace pepper { namespace json { namespace type { namespace str {

  field::field(obj::value &obj, const std::string &name)
    : type::field<str::value>{ obj, name }
  {
    // DO NOTHING
  }

} } } }
