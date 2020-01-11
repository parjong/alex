#include <adapter/cmake/spec.hpp>
#include <adapter/cmake/command.hpp>

namespace adapter { namespace cmake { 

  const sources &sources::emplace(const boost::filesystem::path &p) const
  {
    _vec.emplace_back(p);
    return *this;
  }

  sources::sources(std::vector<boost::filesystem::path> &vec) : _vec(vec)
  {
    // DO NOTHING
   }

} }

namespace adapter { namespace cmake { namespace project { namespace out {
  
  spec::spec(const std::string &name) : _name{ name }
  {
    // DO NOTHING
  }

  adapter::cmake::sources spec::sources(void)
  {
    return adapter::cmake::sources( _sources );
  }

} } } }


namespace adapter { namespace cmake { namespace project { namespace out { namespace exe {
  
  spec::spec(const std::string &name) : out::spec{ name }
  {
    // DO NOTHING
  }

  void spec::dump_into(std::ostream &os) const
  {
    if ( _sources.size() == 0 ) return;

    adapter::cmake::command cmd{ "add_executable" };

    cmd.args().emplace_back( _name );

    for (const auto &source : _sources)
    {
      cmd.args().emplace_back( source.string() );
    }

    cmd.dump_into(os);
  }

} } } } }

namespace adapter { namespace cmake { namespace project { namespace out { namespace lib {
  
  spec::spec(const std::string &name) : out::spec{ name }
  {
    // DO NOTHING
  }

  void spec::dump_into(std::ostream &os) const
  {
    if ( _sources.size() == 0 ) return;

    adapter::cmake::command cmd{ "add_library" };

    cmd.args().emplace_back( _name );

    for (const auto &source : _sources)
    {
      cmd.args().emplace_back( source.string() );
    }

    cmd.dump_into(os);
  }

} } } } }

namespace adapter { namespace cmake { namespace project {

  spec::spec(const std::string &name) : _name{ name }
  {
    // DO NOTHING
  }

  void spec::emplace_compile_option(const std::string &opt)
  {
    _options.emplace_back(opt);
  }

  void spec::emplace_include(const std::string &include)
  {
    _includes.emplace_back(include);
  }

  out::lib::spec &spec::emplace_library(const std::string &name)
  {
    return *_libraries.emplace(_libraries.end(), name);
  }

  out::exe::spec &spec::emplace_executable(const std::string &name)
  {
    return *_executables.emplace(_executables.end(), name);
  }


  void spec::dump_into(std::ostream &os) const
  {
    adapter::cmake::command cmd{ "project" };

    cmd.args().emplace_back( _name );

    cmd.dump_into(os);

    if ( _options.size() > 0 ) {
      os << std::endl;
 
      adapter::cmake::command copt{ "add_compile_options" };

      for (const auto &option : _options)
      {
        copt.args().emplace_back( "\"" + option + "\"");
      }

      copt.dump_into(os);
    }

    if ( _includes.size() > 0 ) {
      os << std::endl;

      adapter::cmake::command cinc{ "include_directories" };

      for (const auto &include : _includes)
      {
        cinc.args().emplace_back( "\"" + include + "\"");
      }

      cinc.dump_into(os);
    }

    for (const auto &library : _libraries)
    {
      os << std::endl;
      library.dump_into(os);
    }

    for (const auto &executable : _executables)
    {
      os << std::endl;
      executable.dump_into(os);
    }
  }

} } }

namespace adapter { namespace cmake {

  spec::spec(const std::string &version)
    : _version{ version }
  {
    // DO NOTHING
  }

  project::spec &spec::emplace_project(const std::string &name)
  { 
    return *_projects.emplace(_projects.end(), name);
  }

  void spec::dump_into(std::ostream &os) const
  {
    os << "cmake_minimum_required(VERSION " << _version << ")" << std::endl;

    for (const auto &project : _projects)
    {
      os << std::endl;
      project.dump_into(os);
    }
  }

} }
