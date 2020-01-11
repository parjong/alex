#include <pepper/interop/lua51/binder/object.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace binder {

  object::object(const state &s) : _state{s}
  {
    // DO NOTHING
  }

  void object::push(const binding::entry &entry)
  {
    auto it = _bindings.emplace(_bindings.end(), entry);

    (*it).load(_state);
  }

} } } }
