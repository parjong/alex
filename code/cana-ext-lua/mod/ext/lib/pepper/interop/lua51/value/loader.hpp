#ifndef __PEPPER_INTEROP_LUA51_VALUE_LOADER_H__
#define __PEPPER_INTEROP_LUA51_VALUE_LOADER_H__

#include <pepper/interop/lua51/state.hpp>
#include <pepper/interop/lua51/code/loader.hpp>
#include <pepper/interop/lua51/stack/accessor.hpp>
#include <pepper/interop/lua51/stack/object.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace value {

  struct loader
  {
    loader() = default;
    virtual ~loader() = default;

    virtual void load(state s) const = 0;
  };

} } } }

#endif
