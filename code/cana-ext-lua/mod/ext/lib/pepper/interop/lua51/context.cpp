#include <pepper/interop/lua51/context.hpp>

namespace pepper { namespace interop { namespace lua51 {

  context::context(state s) : _heap{s}, _stack{s}, _binder{s}
  {
    // DO NOTHING
  }

  heap::object &context::heap(void)
  {
    return _heap;
  }

  stack::object &context::stack(void)
  {
    return _stack;
  }

  binder::object &context::binder(void)
  {
    return _binder;
  }

} } }
