#ifndef __PEPPER_INTEROP_LUA51_FUNCTION_INTERNAL_LOADER_H__
#define __PEPPER_INTEROP_LUA51_FUNCTION_INTERNAL_LOADER_H__

#include <pepper/interop/lua51/function/loader.hpp>

#include <string>

namespace pepper { namespace interop { namespace lua51 { namespace function { namespace internal {

  struct loader : public function::loader
  {
    private:
      std::string _name;

    public:
      loader(const std::string &name);
      virtual ~loader() = default;

    public:
      virtual void load(state s) const;
  };

} } } } }

#endif
