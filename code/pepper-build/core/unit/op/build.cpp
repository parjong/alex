#include <core/unit/op/build.hpp>

#include <pepper/exn.hpp>
#include <pepper/logging.hpp>

namespace core { namespace unit { namespace op { namespace build {

  runner::runner(const core::fwk::manager &frameworks) : _frameworks( frameworks )
  {
    // DO NOTHING
  }

  bool runner::build(const unit::desc &unit) const
  {
    static pepper::logging::logger log{ "pepperbuild.unit.op.builder.build" };
 
    log.info( "process unit at '", unit.root().path(), "'" );

    const core::fwk::name fwk_name{ unit.manifest().framework() };

    auto framework_base = _frameworks.lookup( fwk_name );

    const auto &type = unit.manifest().type();

    log.info( "find a project type descriptor for ", type );

    auto &ctxt = framework_base->types();

    auto it = ctxt.find( type );

    if ( it == ctxt.end() )
    {
      pepper::exn::raise("'", type, "' is not supported");
    }

    log.info( "execute" );

    it->second->build( unit );
  }

} } } }
