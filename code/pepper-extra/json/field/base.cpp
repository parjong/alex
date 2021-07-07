#include "pepper/json/field/base.hpp"
#include "pepper/json/value/object.hpp"

namespace pepper { namespace json {

  field::field(object &o, const std::string &name_)
    : name{ name_ }
  {
    o.add( *this );
  }

  field::field(json::meta &meta, const std::string &name_)
    : name{ name_ }
  {
    meta.add( *this );
  }

} }
