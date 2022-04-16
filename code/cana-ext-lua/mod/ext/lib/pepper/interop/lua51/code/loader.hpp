#ifndef __PEPPER_INTEROP_LUA51_CODE_LOADER_H__
#define __PEPPER_INTEROP_LUA51_CODE_LOADER_H__

#include <pepper/interop/lua51/state.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace code {

  struct loader
  {
    loader() = default;
    virtual ~loader() = default;

    virtual void load(state s) const = 0;
  };

} } } }

#endif
