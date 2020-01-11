#include <pepper/interop/lua51/binding/object.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace binding {

  object::object(const entry &e) : _entry{e}
  {
    // DO NOTHING
  }

  int object::invoke(lua51::stack::object &s) const
  {
    return _entry(s);
  }

} } } }
