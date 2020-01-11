#include <core/project/op/build.hpp>
#include <core/unit/op/build.hpp>

#include <pepper/logging.hpp>

namespace core { namespace project { namespace op { namespace build {

  runner::runner(const core::unit::op::build::runner &ubuild) : _ubuild(ubuild)
  {
    // DO NOTHING
  }

  bool runner::build(const project::desc &p)
  {
    static pepper::logging::logger log{ "pepperbuild.project.op.runner.build" };

    log.trace( p.manifest() );

    for (const auto &unit : p.units())
    {
      log.info( "build a unit at '", unit->root().path(), "' using a unit runner" );
      _ubuild.build( *unit );
    }
  }

} } } }
