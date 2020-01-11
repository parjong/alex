#include <native/toolchain/build/cmake/base.hpp>
#include <adapter/cmake.hpp>

#include <pepper/exn.hpp>
#include <pepper/fs.hpp>
#include <pepper/pathname.hpp>
#include <pepper/logging.hpp>

#include <queue>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace 
{

  struct generator : public native::artifact::visitor
  {
    private:
      const core::unit::desc &_unit;
      adapter::cmake::project::spec &_project;

    public:
      generator(const core::unit::desc &unit, adapter::cmake::project::spec &project) 
        : _unit(unit), _project(project)
      {
        // DO NOTHING
      }

    public:
      virtual ~generator() = default;

    private:
      void append_sources(adapter::cmake::project::out::spec &out)
      {
        static pepper::logging::logger log{ "pepperbuild.append_sources" };

        pepper::fs::collector c;

        pepper::pathname::glob pattern{ "pepper/**/*.cpp" };
        pepper::fs::globbing_visitor visitor{ pattern };

        auto append_fn = [&] (const boost::filesystem::path &b, const boost::filesystem::path &r)
        {
          log.trace( "add ", r, " as a source" );
          out.sources().emplace(r);
        };

        visitor.add_function(append_fn);
        c.collect( _unit.root().path(), visitor );  
      }

    public:
      virtual void visit(const native::artifact::lib &) 
      {
        auto &lib = _project.emplace_library( _unit.name().string() );

        append_sources( lib );
      }

    public:
      virtual void visit(const native::artifact::exe &)
      {
        auto &exe = _project.emplace_executable( _unit.name().string() );

        append_sources( exe );
      }
  };

}

namespace native { namespace toolchain { namespace build { namespace cmake {

  void base::build(const core::unit::desc &unit, const native::artifact::base &out) const
  {
    static pepper::logging::logger log{ "pepperbuild.native.toolchain.build.cmake.base" };

    // Create CMakeLists.txt from pepper-project.json
    adapter::cmake::spec cmake_spec("2.8.8");
    
    auto &cmake_project = cmake_spec.emplace_project( unit.name().string() );

    cmake_project.emplace_compile_option("-std=c++11");
    cmake_project.emplace_include(".");

    ::generator gen{ unit, cmake_project };
  
    out.accept(gen);

    {
      boost::filesystem::fstream fs( unit.root().path() / "CMakeLists.txt", std::ios::out );

      cmake_spec.dump_into( fs );
    }

    auto cmd = pepper::fmt::make("cd ", unit.root().path(), "; mkdir -p .pepper; cd .pepper; cmake ..; make");

    std::stringstream ss;

    ss << cmd;

    system( ss.str().c_str() );

    log.warn( "not fully implemented yet" );
  }

} } } }
