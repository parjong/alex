#include <core/unit/pathname/root.hpp>

namespace core { namespace unit { namespace pathname {

  manifest::manifest(const boost::filesystem::path &r) : file{ r }
  {
    // DO NOTHING
  }

  root::root(const boost::filesystem::path &r) : dir{ r }
  {
    // DO NOTHING
  }

  pathname::manifest root::manifest(void) const
  {
    return pathname::manifest{ path() / "pepper-unit.json" };
  }

} } }
