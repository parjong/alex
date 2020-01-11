#ifndef __PEPPER_INTEROP_LUA51_FUNCTION_EXTERNAL_LOADER_H__
#define __PEPPER_INTEROP_LUA51_FUNCTION_EXTERNAL_LOADER_H__

#include <pepper/interop/lua51/function/loader.hpp>
#include <pepper/interop/lua51/binding.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace function { namespace external {

  struct loader : public function::loader
  {
    private:
      binding::loader _loader;

    public:
      loader(const binding::entry &f);
      virtual ~loader() = default;

    public:
      virtual void load(state s) const;
  };

} } } } }

#endif
