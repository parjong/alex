#include <core/project/data.hpp>

#include <core/project/desc.hpp>

#include <pepper/fs.hpp>
#include <pepper/mem.hpp>

#include <boost/filesystem/fstream.hpp>

namespace {

  std::unique_ptr<core::project::manifest::spec> init_manifest(core::project::data &d)
  {
    auto o = pepper::mem::unique::make<core::project::manifest::spec>();

    boost::filesystem::ifstream is{ d.base().root().manifest().path() };

    is >> *o;

    return o;
  }

  std::unique_ptr<core::unit::ctxt> init_units(core::project::data &d)
  {
    auto o = pepper::mem::unique::make<core::unit::ctxt>();

    for ( boost::filesystem::directory_iterator it{ d.base().root().units().path() }; it != boost::filesystem::directory_iterator{}; ++it)
    {
      o->emplace_back( new core::unit::desc{ it->path() } );
    }

    return o;
  }

}

namespace core { namespace project {

  data::data(const core::project::desc &base) 
    : _base( base )
    , manifest{ [&](void) { return ::init_manifest(*this); } }
    , units{ [&](void) { return ::init_units(*this); } }
  {
    // DO NOTHING
  }


  const core::project::desc &data::base(void) const
  {
    return _base;
  }

} }
