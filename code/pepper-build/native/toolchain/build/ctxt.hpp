#ifndef __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_CTXT_H__
#define __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_CTXT_H__

#include <native/toolchain/build/base.hpp>

#include <map>
#include <memory>
#include <string>

namespace native { namespace toolchain { namespace build {

  struct ctxt : public std::map<std::string, std::unique_ptr<build::base>>
  {
    ctxt() = default;
    virtual ~ctxt() = default;
  };

} } }

#endif
