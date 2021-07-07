#include <pepper/interop/lua51/stack/accessor.hpp>

extern "C"
{
	#include "lua.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace stack {

  int accessor<int>::pop(state s)
  {
    int res = lua_tointeger(s, -1);
    lua_pop(s, 1);
    return res;
  }

  void accessor<int>::push(state s, const int &v)
  {
    lua_pushinteger(s, v);
  }

} } } }

namespace pepper { namespace interop { namespace lua51 { namespace stack {

  std::string accessor<std::string>::pop(state s)
  {
    const char *str = lua_tostring(s, -1);
    lua_pop(s, 1);
    return str;
  }

  void accessor<std::string>::push(state s, const std::string &v)
  {
    lua_pushstring(s, v.c_str());
  }

} } } }
