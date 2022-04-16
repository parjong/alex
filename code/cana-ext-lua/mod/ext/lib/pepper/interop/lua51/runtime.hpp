#ifndef __PEPPER_INTEROP_LUA51_RUNTIME_H__
#define __PEPPER_INTEROP_LUA51_RUNTIME_H__

#include <pepper/interop/lua51/state.hpp>
#include <pepper/interop/lua51/code.hpp>
#include <pepper/interop/lua51/context.hpp>
#include <pepper/interop/lua51/value.hpp>
#include <pepper/interop/lua51/function.hpp>

#include <pepper/mem.hpp>

namespace pepper { namespace interop { namespace lua51 {

  class runtime
  {
    private:
      state _state;
      std::unique_ptr<context> _context;

    public:
      runtime();
      ~runtime();

    public:
      heap::object &heap(void);
      stack::object &stack(void);
      binder::object &binder(void);

    public:
      void  load(const code::loader &code);
      int   eval(void);

    public:
      void  invoke(int nargs, int nresults = -1);

    public:
      template <typename... Args> void call(const function::loader &f, const Args&... args)
      {
        f.load(_state);

        const int nargs = sizeof...(args);
        const value::typed::bean beans[nargs] = { args... };

        for (int i = 0; i < nargs; ++i)
        {
          beans[i].load(_state);
        }

        invoke(nargs);
      }

      template <typename... Args> void call(const std::string &func, const Args&... args)
      {
        pepper::interop::lua51::function::internal::loader f{func};
        call(f, args...);
      }

      template <typename... Args> void call(const binding::entry &func, const Args&... args)
      {
        pepper::interop::lua51::function::external::loader f{func};
        call(f, args...);
      }
  };

} } }

#endif
