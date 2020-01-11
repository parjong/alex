#include "pepper/lua.hpp"

namespace pepper
{
  namespace lua
  {
    interp::interp() 
      : _state( luaL_newstate() )
    {
      luaL_openlibs(_state);          
      luabind::open(_state);
    }

    interp::~interp()
    {
      lua_close(_state);
    }

    void interp::load(const boost::filesystem::path &path)
    {
      luaL_loadfile(_state, path.string().c_str());
    }

    void interp::put(const std::string &var, const std::string &val)
    {
      lua_pushstring(_state, val.c_str());
      lua_setglobal(_state, var.c_str());
    }

    void interp::run(void)
    {
      lua_call(_state, 0, 0);
    }


  }
}
