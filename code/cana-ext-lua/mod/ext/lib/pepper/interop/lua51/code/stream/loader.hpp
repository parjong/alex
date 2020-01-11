#ifndef __PEPPER_INTEROP_LUA51_CODE_STREAM_LOADER_H__
#define __PEPPER_INTEROP_LUA51_CODE_STREAM_LOADER_H__

#include <pepper/interop/lua51/code/loader.hpp>

#include <istream>

namespace pepper { namespace interop { namespace lua51 { namespace code { namespace stream {

  class loader : public code::loader
  {
    private:
      std::istream &_is;

    public:
      loader(std::istream &);
      virtual ~loader() = default;

    public:
      virtual void load(state s) const;
  };

} } } } }

#endif
