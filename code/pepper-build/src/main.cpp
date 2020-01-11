#include <pepper/env.hpp>
#include <pepper/exn.hpp>
#include <pepper/appfw.hpp>
#include <pepper/mem.hpp>
#include <pepper/logging.hpp>

#include <src/command/build.hpp>

namespace {

  class domain
  {
    private:
      const std::string _root;

    public:
      int run(int argc, char **argv);

    public:
      domain(const std::string &root) : _root{ root } 
      {
        // DO NOTHING
      }

    public:
      ~domain() = default;
  };

  int domain::run(int argc, char **argv) {

    cfg::ctxt ctxt{ _root };

		auto app = pepper::mem::shared::make<pepper::appfw::apps::nested::desc>();

    (*app)
      .command( "build" )
      .set( pepper::mem::unique::make<command::build>(ctxt) );

		pepper::appfw::cli::host host{app};
		pepper::appfw::cli::args::block::desc args{argc, argv};

    return host.run(args);
  }
}

int main(int argc, char **argv) {

  pepper::logging::configure();

  pepper::env::reader root{ "PEPPER_BUILD_ROOT" };

  int res = 255;

  auto action_fn = [&] (const std::string &root)
  {
    ::domain d{ root };

    res = d.run(argc, argv);
  };

  if ( !root.read( action_fn ) )
  {
    pepper::exn::raise( "PEPPER_BUILD_ROOT should be specified" );
  }

  return res;
}
