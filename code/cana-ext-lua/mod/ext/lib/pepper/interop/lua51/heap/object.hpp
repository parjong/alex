#ifndef __PEPPER_INTEROP_LUA51_HEAP_OBJECT_H__
#define __PEPPER_INTEROP_LUA51_HEAP_OBJECT_H__

#include <pepper/interop/lua51/state.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace heap {

  class object
  {
    private:
      state _state;

    public:
      object(state s);

    public:
      void load(const std::string &name);
      void store(const std::string &name);
  };

} } } }

#endif
