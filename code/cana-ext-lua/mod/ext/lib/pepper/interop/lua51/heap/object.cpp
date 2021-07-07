#include <pepper/interop/lua51/heap/object.hpp>

extern "C"
{
	#include "lua.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace heap {

  object::object(state s) : _state{s}
  {
    // DO NOTHING
  }

  void object::load(const std::string &k)
  {
    lua_getfield(_state, LUA_GLOBALSINDEX, k.c_str());
  }

  void object::store(const std::string &k)
  {
    lua_setfield(_state, LUA_GLOBALSINDEX, k.c_str());
  }

} } } }
