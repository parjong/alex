#ifndef __PEPPER_BUILD_NATIVE_TOOLCHIAN_BUILD_INTERNAL_BASE_H__
#define __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_INTERMAL_BASE_H__

#include <native/toolchain/compile/factory.hpp>
#include <native/toolchain/build/base.hpp>

namespace native { namespace toolchain { namespace build { namespace internal {

  class base : public native::toolchain::build::base
  {
    private:
      const native::toolchain::compile::factory &_factory;

    public:
      base(const native::toolchain::compile::factory &factory);
      virtual ~base() = default;

    public:
      virtual void build(const core::unit::desc &unit, const native::artifact::base &out) const;
  };

} } } }

#endif
