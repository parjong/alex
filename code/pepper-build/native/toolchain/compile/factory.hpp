#ifndef __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_FACTORY_H__
#define __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_FACTORY_H__

#include <native/toolchain/compile/instance.hpp>

#include <memory>

namespace native { namespace toolchain { namespace compile {

  struct factory
  {
    factory() = default;
    virtual ~factory() = default;

    virtual std::unique_ptr<instance> create(void) const = 0;
  };

} } }

#endif
