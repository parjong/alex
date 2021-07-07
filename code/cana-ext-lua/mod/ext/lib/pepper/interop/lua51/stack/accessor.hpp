#ifndef __PEPPER_INTEROP_LUA51_STACK_ACCESSOR_H__
#define __PEPPER_INTEROP_LUA51_STACK_ACCESSOR_H__

#include <pepper/interop/lua51/state.hpp>

#include <string>

namespace pepper { namespace interop { namespace lua51 { namespace stack {

  template <typename T> struct accessor
  {
    static T    pop(state s);
    static void push(state s, const T &v);
  };

  template <> struct accessor<int>
  {
    static int  pop(state s);
    static void push(state s, const int &v);
  };

  template <> struct accessor<std::string>
  {
    static std::string pop(state s);
    static void push(state s, const std::string &v);
  };


} } } }

#endif
