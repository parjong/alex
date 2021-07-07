#ifndef __PEPPER_INTEROP_LUA51_BINDING_OBJECT_H__
#define __PEPPER_INTEROP_LUA51_BINDING_OBJECT_H__

#include <pepper/interop/lua51/binding/entry.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace binding {

  class object
  {
    private:
      entry _entry;

    public:
      object(const entry &e);

    public:
      int invoke(lua51::stack::object &s) const;
  };

} } } }

#endif
