#include <cana/corelib/binding/json/package.hpp>

namespace fs = boost::filesystem;

namespace cana { namespace corelib { namespace binding { namespace json {

  package::package(const fs::path &base)
  {
    _base = base;
  }

  fs::path package::resolve(const fs::path &p) const
  {
    return absolute(p, _base);
  }

} } } }
