#include <native/toolchain/compile/gcc/factory.hpp>
#include <native/toolchain/compile/gcc/instance.hpp>

namespace native { namespace toolchain { namespace compile { namespace gcc {

  std::unique_ptr<compile::instance> factory::create(void) const
  {
    return std::unique_ptr<compile::instance>{ new gcc::instance{ } };
  }

} } } }
