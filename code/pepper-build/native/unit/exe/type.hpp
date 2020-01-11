#ifndef __PEPPER_BUILD_NATIVE_UNIT_EXE_TYPE_H__
#define __PEPPER_BUILD_NATIVE_UNIT_EXE_TYPE_H__

#include <core/unit/type/base.hpp>

#include <native/toolchain/build/base.hpp>

namespace native { namespace unit { namespace cxx { namespace exe {

  class type : public core::unit::type::base
  {
    private:
      const native::toolchain::build::base &_toolchain;

    public:
      type(const native::toolchain::build::base &toolchain);
      virtual ~type() = default;

    public:
      virtual void build(const core::unit::desc &p); 
  };

} } } }

#endif
