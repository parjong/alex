#include "core/project/pathname/root.hpp"

namespace core { namespace project { namespace pathname { 

  manifest::manifest(const boost::filesystem::path &path)
    : file{ path }
  {
    // DO NOTHING
  }

  units::units(const boost::filesystem::path &path)
    : dir{ path }
  {
    // DO NOTHING
  }

  root::root(const boost::filesystem::path &path)
    : dir{ path }
  {
    // DO NOTHING
  }

  pathname::manifest root::manifest(void) const
  {
    return pathname::manifest{ path() / "pepper-project.json" };
  }

  pathname::units root::units(void) const
  {
    return pathname::units{ path() / "units" };
  }

} } }
