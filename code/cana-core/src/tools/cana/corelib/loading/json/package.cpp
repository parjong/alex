#include <cana/corelib/loading/json/package.hpp>

namespace fs = boost::filesystem;

namespace cana { namespace corelib { namespace loading { namespace json {

  package::package(const fs::path &base)
  {
    _base = base;
  }

  fs::path package::resolve(const fs::path &p) const
  {
    return absolute(p, _base);
  }

} } } }
