#ifndef __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_SPEC_H__
#define __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_SPEC_H__

#include <pepper/json.hpp>

namespace native { namespace toolchain { namespace build {

  namespace js = pepper::json::type;

  struct spec : public js::obj::value
  {
    js::str::field type;

    spec() : type{ *this, "type" }
    {
      // DO NOTHING
    }

    virtual ~spec() = default;
  };

} } }

#endif
