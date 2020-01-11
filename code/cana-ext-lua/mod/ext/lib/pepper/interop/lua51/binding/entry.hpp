#ifndef __PEPPER_INTEROP_LUA51_BINDING_ENTRY_H__
#define __PEPPER_INTEROP_LUA51_BINDING_ENTRY_H__

#include <pepper/interop/lua51/stack.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace binding {

  typedef std::function<int (lua51::stack::object &)> entry;

} } } }

#endif
