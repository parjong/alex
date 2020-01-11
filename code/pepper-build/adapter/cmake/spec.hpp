#ifndef __PEPPERBUILD_ADAPTER_CMAKE_SPEC_H_
#define __PEPPERBUILD_ADAPTER_CMAKE_SPEC_H__

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace adapter { namespace cmake {

  class sources
  {
    private:
      std::vector<boost::filesystem::path> &_vec;

    public:
      const sources &emplace(const boost::filesystem::path &p) const;

    public:
      sources(std::vector<boost::filesystem::path> &vec);
      ~sources() = default;
  };

} }

namespace adapter { namespace cmake { namespace project { namespace out {

  class spec
  {
    protected:
      std::string _name;

    public:
      spec(const std::string &name);
      ~spec() = default;

    protected:
      std::vector<boost::filesystem::path> _sources;
    public:
      adapter::cmake::sources sources(void);

    public:
      virtual void dump_into(std::ostream &os) const = 0;
  };

} } } }


namespace adapter { namespace cmake { namespace project { namespace out { namespace exe {

  class spec : public out::spec
  {
    public:
      spec(const std::string &name);
      ~spec() = default;

    public:
      virtual void dump_into(std::ostream &os) const;
  };

} } } } }


namespace adapter { namespace cmake { namespace project { namespace out { namespace lib {

  class spec : public out::spec
  {
    public:
      spec(const std::string &name);
      ~spec() = default;

    public:
      virtual void dump_into(std::ostream &os) const;
  };

} } } } }

namespace adapter { namespace cmake { namespace project {

  class spec 
  {
    private:
      std::string _name;

    public:
      spec(const std::string &name);
      ~spec() = default;

    private:
      std::vector<std::string> _options;
    public:
      void emplace_compile_option(const std::string &opt);

    private:
      std::vector<std::string> _includes;
    public:
      void emplace_include(const std::string &include);

    private:
      std::vector<out::lib::spec> _libraries;
    public:
      out::lib::spec &emplace_library(const std::string &name);

    private:
      std::vector<out::exe::spec> _executables;
    public:
      out::exe::spec &emplace_executable(const std::string &name);

    public:
      void dump_into(std::ostream &os) const;
  };

} } }

namespace adapter { namespace cmake {

  // CMakeLists.txt
  class spec 
  {
    private:
      std::string _version;
 
    public:
      spec(const std::string &version);
      ~spec() = default;

    private:
      std::vector<project::spec> _projects;
    public:
      project::spec &emplace_project(const std::string &name);

    public:
      void dump_into(std::ostream &os) const;
  };

} }

#endif
