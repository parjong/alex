#ifndef __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_GCC_INSTANCE_H__
#define __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_GCC_INSTANCE_H__

#include <native/toolchain/compile/instance.hpp>

namespace native { namespace toolchain { namespace compile { namespace gcc {

  class instance : public native::toolchain::compile::instance
  {
    public:
      instance() = default;
      virtual ~instance() = default;

    public:
      virtual void run(void) const;
  };

} } } }

#endif
