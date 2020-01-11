#include <native/toolchain/build/internal/base.hpp>

#include <pepper/exn.hpp>
#include <pepper/logging.hpp>

namespace native { namespace toolchain { namespace build { namespace internal {

  base::base(const native::toolchain::compile::factory &factory) : _factory(factory)
  {
    // DO NOTHING
  }

  void base::build(const core::unit::desc &unit, const native::artifact::base &out) const
  {
    static pepper::logging::logger log{ "pepperbuild.native.toolchain.build.internal.base" };

    pepper::exn::raise( "not fully implemented yet" );
  }

} } } }
