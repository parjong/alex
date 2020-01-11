#ifndef __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_GCC_FACTORY_H__
#define __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_GCC_FACTORY_H__

#include <native/toolchain/compile/factory.hpp>

namespace native { namespace toolchain { namespace compile { namespace gcc {

  class factory : public native::toolchain::compile::factory
  {
    public:
      factory() = default;
      virtual ~factory() = default;

    public:
      virtual std::unique_ptr<compile::instance> create(void) const;
  };

} } } }

#endif
