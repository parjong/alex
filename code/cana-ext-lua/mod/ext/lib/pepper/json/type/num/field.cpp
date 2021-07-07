#include <pepper/json/type/num/field.hpp>

namespace pepper { namespace json { namespace type { namespace num {

  field::field(obj::value &obj, const std::string &name)
    : type::field<num::value>{ obj, name }
  {
    // DO NOTHING
  }

} } } }
