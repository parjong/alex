#ifndef __PEPPER_INTEROP_LUA51_BINDER_OBJECT_H__
#define __PEPPER_INTEROP_LUA51_BINDER_OBJECT_H__

#include <pepper/interop/lua51/binding.hpp>
#include <pepper/interop/lua51/state.hpp>
#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace interop { namespace lua51 { namespace binder {

  class object
  {
    private:
      state _state;
      std::vector<binding::loader> _bindings;

    public:
      object(const state &s);

    public:
      void push(const binding::entry &);
  };

} } } }

#endif
