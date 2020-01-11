#include <cfg/ctxt.hpp>
#include <cfg/spec.hpp>

#include <native/fwk/base.hpp>

#include <native/toolchain/compile/gcc/factory.hpp>
#include <native/toolchain/build/internal/base.hpp>
#include <native/toolchain/build/cmake/base.hpp>

#include <native/unit/lib/type.hpp>
#include <native/unit/exe/type.hpp>

#include <pepper/mem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace cfg {

  const core::fwk::manager &ctxt::frameworks(void) const
  {
    return _frameworks;
  }

  ctxt::ctxt(const boost::filesystem::path &root)
  {
    cfg::spec _spec;
   
    //
    boost::filesystem::fstream is{ root / "config" / "settings.json" };

    is >> _spec;

    // log.info( "initialize app type(s)" );

    native::toolchain::compile::gcc::factory fac{ };

    //
    _toolchains["internal"] =
      pepper::mem::unique::make<native::toolchain::build::internal::base>(fac);
    _toolchains["cmake"] =
      pepper::mem::unique::make<native::toolchain::build::cmake::base>();

    //
    const auto &toolchain = _toolchains[ _spec.native().type() ];

    //
    _types["lib"] = 
      pepper::mem::unique::make<native::unit::cxx::lib::type>( *toolchain );
    _types["exe"] =
      pepper::mem::unique::make<native::unit::cxx::exe::type>( *toolchain );

    //
    _frameworks
      .add( pepper::mem::unique::make<native::fwk::base>(_types) )
      .name( "native" );
  }

}
