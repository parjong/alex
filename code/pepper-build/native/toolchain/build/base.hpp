#ifndef __NATIVE_TOOLCHAIN_BUILD_BASE_H__
#define __NATIVE_TOOLCHAIN_BUILD_BASE_H__

#include <core/unit/desc.hpp>
#include <native/artifact/base.hpp>

namespace native { namespace toolchain { namespace build {

  struct base {
    base() = default;
    virtual ~base() = default;

    virtual void build(const core::unit::desc &unit, const native::artifact::base &artifact) const = 0;
  };

} } }

#endif
