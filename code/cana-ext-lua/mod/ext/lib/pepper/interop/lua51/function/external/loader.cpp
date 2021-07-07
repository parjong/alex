#include <pepper/interop/lua51/function/external/loader.hpp>

extern "C"
{
  #include "lua.h"
}

namespace pepper { namespace interop { namespace lua51 { namespace function { namespace external {

  loader::loader(const binding::entry &entry) : _loader{entry}
  {
    // DO NOTHING
  }

  void loader::load(state s) const
  {
    _loader.load(s);
  }

} } } } }
