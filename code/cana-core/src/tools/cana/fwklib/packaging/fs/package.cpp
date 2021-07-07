#include "package.hpp"

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  package::package(const boost::filesystem::path &base)
  {
    _base = base;
  }

  std::string package::resolve(const std::string &p) const
  {
    return absolute(p, _base).native();
  }

} } } }
