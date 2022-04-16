#include "storage.hpp"

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  storage::storage(const boost::filesystem::path &base)
  {
    _base = base;
  }

  void storage::make(void)
  {
    create_directories(_base);
  }

  std::string storage::resolve(const std::string &p) const
  {
    return absolute(p, _base).native();
  }

} } } }
