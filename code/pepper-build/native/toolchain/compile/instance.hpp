#ifndef __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_INSTANCE_H__
#define __PEPPERBUILD_NATIVE_TOOLCHAIN_COMPILE_INSTANCE_H__

namespace native { namespace toolchain { namespace compile {

  struct instance
  {
    instance() = default;
    virtual ~instance() = default;

    virtual void run(void) const = 0;
  };

} } }

#endif
