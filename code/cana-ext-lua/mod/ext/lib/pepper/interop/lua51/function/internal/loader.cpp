#include <pepper/interop/lua51/function/internal/loader.hpp>

extern "C"
{
	#include "lua.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace function { namespace internal {

  loader::loader(const std::string &name) : _name{name}
  {
    // DO NOTHING
  }

  void loader::load(state s) const
  {
    lua_getglobal(s, _name.c_str());
  }

} } } } }
