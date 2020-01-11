#include "storage.hpp"

namespace fs = boost::filesystem;

namespace cana { namespace core {

  storage::storage(const fs::path &base)
  {
    _base = base;
  }

  fs::path storage::resolve(const fs::path &p) const
  {
    return absolute(p, _base);
  }

} }
