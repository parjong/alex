#ifndef __PEPPER_BUILD_NATIVE_TOOLCHIAN_BUILD_CMAKE_BASE_H__
#define __PEPPER_BUILD_NATIVE_TOOLCHAIN_BUILD_CMAKE_BASE_H__

#include <native/toolchain/build/base.hpp>

namespace native { namespace toolchain { namespace build { namespace cmake {

  struct base : public native::toolchain::build::base
  {
    base() = default;
    virtual ~base() = default;

    virtual void build(const core::unit::desc &unit, const native::artifact::base &out) const;
  };

} } } }

#endif
