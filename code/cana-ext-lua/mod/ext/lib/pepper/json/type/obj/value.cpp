#include <pepper/json/type/obj/value.hpp>

namespace pepper { namespace json { namespace type { namespace obj {

  void value::add_field(const std::string &name, type::value &field)
  {
    _meta.add( name, field );
  }

  void value::load_from(const cursor::object &curr)
  {
    _meta.load_from( curr );
  }

  void value::dump_into(cursor::object &curr) const
  {
    _meta.dump_into( curr );
  }

} } } }
