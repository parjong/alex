#ifndef __PEPPER_BUILD_CFG_H__
#define __PEPPER_BUILD_CFG_H__

#include <pepper/json.hpp>

#include <native/toolchain/build/spec.hpp>

namespace cfg {

  namespace js = pepper::json::type;

  struct spec : public js::obj::value
  {
    js::field<native::toolchain::build::spec> native;

    spec();
    virtual ~spec() = default;
  };

}

#endif
