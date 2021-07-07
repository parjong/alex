#ifndef __PEPPER_INTEROP_LUA51_FUNCTION_LOADER_H__
#define __PEPPER_INTEROP_LUA51_FUNCTION_LOADER_H__

#include <pepper/interop/lua51/state.hpp>
#include <pepper/interop/lua51/value/loader.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace function {

  struct loader : public value::loader
  {
    loader() = default;
    virtual ~loader() = default;
  };

} } } }

#endif
