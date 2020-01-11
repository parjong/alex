#include <native/unit/exe/type.hpp>

#include <native/artifact/base.hpp>
#include <native/toolchain/build/cmake/base.hpp>

namespace native { namespace unit { namespace cxx { namespace exe {

  type::type(const native::toolchain::build::base &toolchain) : _toolchain(toolchain)
  {
    // DO NOTHING
  }

  void type::build(const core::unit::desc &unit) 
  {
    native::artifact::exe out{ };

    _toolchain.build(unit, out);
  }

} } } }
