#include <command/build.hpp>

#include <core/project/desc.hpp>
#include <core/project/op/build.hpp>

#include <pepper/logging.hpp>

namespace command {

  build::build(const cfg::ctxt &ctxt) : _ctxt(ctxt)
  {
    // DO NOTHING
  }

  int build::main(pepper::appfw::apps::basic::service &args) 
  {
    static pepper::logging::logger log{ "pepper.command.build.run" };

    log.trace( "enter" );

    core::project::desc p{ boost::filesystem::current_path() };

    core::unit::op::build::runner ubuild{ _ctxt.frameworks() };
    core::project::op::build::runner pbuild{ ubuild };

    pbuild.build( p );

    log.trace( "leave" );

    return 0;
  }

}
