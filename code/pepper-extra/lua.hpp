#ifndef __PEPPER_LUA_H__
#define __PEPPER_LUA_H__

#include <string>
#include <boost/filesystem.hpp>

#include <lua5.2/lua.hpp>
#include <luabind/luabind.hpp>

namespace pepper 
{
  namespace lua
  {
    class interp
    {
      private:
        lua_State *_state;

      public:
        interp(); 
        ~interp();
       
        void load(const boost::filesystem::path &path);
        void put(const std::string &var, const std::string &val);

        template <typename RetType, typename... ArgTypes>
          void def(const std::string &name, RetType (*func)(ArgTypes...))
        { 
          luabind::module(_state) 
          [
            luabind::def(name.c_str(), func)
          ];
        }

        void run(void);
    };
  }

}

#endif
