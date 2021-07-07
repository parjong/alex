#ifndef __PEPPER_INTEROP_LUA51_BINDING_LOADER_H__
#define __PEPPER_INTEROP_LUA51_BINDING_LOADER_H__

#include <pepper/interop/lua51/binding/object.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace binding {

  struct loader
  {
    private:
      std::unique_ptr<binding::object> _eo;

    public:
      loader(const binding::entry &f);

    public:
      void load(state s) const;
  };

} } } }

#endif
