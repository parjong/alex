#include <pepper/interop/lua51/code/string/loader.hpp>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace code { namespace string {

  loader::loader(const std::string &code) : _code{code}
  {
    // DO NOTHING
  }

  void loader::load(state s) const
  {
    luaL_loadstring(s, _code.c_str());
  }

} } } } }
