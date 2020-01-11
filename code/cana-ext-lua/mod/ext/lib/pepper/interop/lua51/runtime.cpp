#include <pepper/interop/lua51/runtime.hpp>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
}

namespace pepper { namespace interop { namespace lua51 {

  runtime::runtime(void) : _state{nullptr}
  {
    _state = lua_open();
    _context = pepper::mem::unique::make<context>(_state);
  }

  runtime::~runtime(void)
  {
    _context.reset(nullptr);
    if (_state != nullptr)
    {
      lua_close(_state);
    }
  }

  heap::object &runtime::heap(void)
  {
    return (*_context).heap();
  }

  stack::object &runtime::stack(void)
  {
    return (*_context).stack();
  }

  binder::object &runtime::binder(void)
  {
    return (*_context).binder();
  }

  void runtime::load(const code::loader &code)
  {
    code.load(_state);
  }

  int runtime::eval(void)
  {
    return lua_pcall(_state, 0, LUA_MULTRET, 0);
  }

  void runtime::invoke(int nargs, int nresults)
  {
    lua_call(_state, nargs, (nresults < 0) ? LUA_MULTRET : nresults);
  }

} } }
