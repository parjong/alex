#ifndef __PEPPER_INTEROP_LUA51_CONTEXT_H__
#define __PEPPER_INTEROP_LUA51_CONTEXT_H__

#include <pepper/interop/lua51/heap.hpp>
#include <pepper/interop/lua51/stack.hpp>
#include <pepper/interop/lua51/binder.hpp>

namespace pepper { namespace interop { namespace lua51 {

  class context
  {
    private:
      heap::object _heap;
      stack::object _stack;
      binder::object _binder;

    public:
      context(state);

    public:
      heap::object &heap(void);
      stack::object &stack(void);
      binder::object &binder(void);
  };

} } }

#endif
