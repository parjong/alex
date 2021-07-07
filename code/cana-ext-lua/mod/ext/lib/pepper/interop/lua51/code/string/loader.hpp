#ifndef __PEPPER_INTEROP_LUA51_CODE_STRING_LOADER_H__
#define __PEPPER_INTEROP_LUA51_CODE_STRING_LOADER_H__

#include <pepper/interop/lua51/code/loader.hpp>

#include <string>

namespace pepper { namespace interop { namespace lua51 { namespace code { namespace string {

  class loader : public code::loader
  {
    private:
      std::string _code;

    public:
      loader(const std::string &);
      virtual ~loader() = default;

    public:
      virtual void load(state s) const;
  };

} } } } }

#endif
