#include "pepper/pathname/relative/base.hpp"

namespace pepper { namespace pathname { namespace relative {
  
  base::base(const boost::filesystem::path &path) 
    : _path(path)
  {
    // DO NOTHING
  }

  const boost::filesystem::path &base::path(void) const 
  { 
    return _path; 
  }

  std::ostream &operator<<(std::ostream &lhs, const base &rhs)
  {
    lhs << rhs.path();
    return lhs;  
  }

  dir::dir(const boost::filesystem::path &path)
    : base{ path }
  {
    // DO NOTHING
  }

  file::file(const boost::filesystem::path &path)
    : base{ path }
  {
    // DO NOTHING
  }

} } }
