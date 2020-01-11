#include <pepper/interop/lua51/binding/loader.hpp>

extern "C"
{
  #include "lua.h"
}

namespace {

  int umthunk(pepper::interop::lua51::state s)
  {
    auto ind = lua_upvalueindex(1);
    auto ptr = (pepper::interop::lua51::binding::object *) lua_topointer(s, ind);

    pepper::interop::lua51::stack::object stk{s};

    return (*ptr).invoke(stk);
  };

}

namespace pepper { namespace interop { namespace lua51 { namespace binding {

  loader::loader(const binding::entry &f)
  {
    _eo = pepper::mem::unique::make<binding::object>(f);
  }

  void loader::load(state s) const
  {
    lua_pushlightuserdata(s, (void *) _eo.get());
    lua_pushcclosure(s, ::umthunk, 1);
  }

} } } }
