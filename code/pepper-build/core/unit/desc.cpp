#include <core/unit/desc.hpp>

namespace core { namespace unit {

  const unit::pathname::root &desc::root(void) const
  {
    return _data->root();
  }

  const unit::name &desc::name(void) const
  {
    return _data->name();
  }

  const unit::manifest::spec &desc::manifest(void) const
  {
    return _data->manifest();
  }

  desc::desc(const boost::filesystem::path &r)
    : _data{ new unit::data{r} }
  {
    // DO NOTHING
  }

} }
