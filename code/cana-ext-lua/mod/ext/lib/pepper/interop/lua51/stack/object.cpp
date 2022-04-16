#include <pepper/interop/lua51/stack/object.hpp>

extern "C"
{
	#include "lua.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace stack {

  object::object(state s) : _state{s}
  {
    // DO NOTHING
  }

  int object::size(void) const
  {
    return lua_gettop(_state);
  }

} } } }
