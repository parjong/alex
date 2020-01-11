#include <core/unit/data.hpp>

#include <pepper/mem.hpp>

#include <boost/filesystem/fstream.hpp>

namespace {

  std::unique_ptr<core::unit::manifest::spec> init_manifest(const core::unit::pathname::root &r)
  {
    auto obj = pepper::mem::unique::make<core::unit::manifest::spec>();

    boost::filesystem::ifstream is{ r.manifest().path() };

    is >> *obj;

    return obj;
  }

  std::unique_ptr<core::unit::name> init_name(const core::unit::pathname::root &r)
  {
    return pepper::mem::unique::make<core::unit::name>( r.path().filename().string() );
  }

}

namespace core { namespace unit {

  const core::unit::pathname::root &data::root(void) const
  {
    return _root;
  }

  data::data(const boost::filesystem::path &r) 
    : _root{ r }
    , name{ [&]() { return ::init_name(this->root()); } }
    , manifest{ [&]() { return ::init_manifest(this->root()); } }
  {
    // DO NOTHING
  }

} }
