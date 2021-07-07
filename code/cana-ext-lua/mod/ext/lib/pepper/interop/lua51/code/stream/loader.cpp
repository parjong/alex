#include <pepper/interop/lua51/code/stream/loader.hpp>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace code { namespace stream {

  loader::loader(std::istream &is) : _is(is)
  {
    // DO NOTHING
  }

  void loader::load(state s) const
  {
    std::string code(std::istreambuf_iterator<char>(_is), {});
    luaL_loadstring(s, code.c_str());
  }

} } } } }
