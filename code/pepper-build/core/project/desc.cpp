#include <core/project/desc.hpp>

namespace core { namespace project {

  desc::desc(const boost::filesystem::path &root) 
    : _data{ new project::data{ *this } }
    , _root{ root }
  {
    // DO NOTHING
  }

  const project::pathname::root &desc::root(void) const
  {
    return _root;
  }

  const project::manifest::spec &desc::manifest(void) const
  {
    return _data->manifest();
  }

  const core::unit::ctxt &desc::units(void) const
  {
    return _data->units();
  }

} }
