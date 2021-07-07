#include "pepper/pathname/base.hpp"

namespace pepper
{
  namespace pathname
  {
    base::base(const boost::filesystem::path &path) 
      : _path(path)
    {
      // DO NOTHING
    }

    const boost::filesystem::path &base::path(void) const 
    { 
      return _path; 
    }

    const std::string base::basename(void) const
    {
      return _path.filename().string();
    }

    bool base::does_exist(void) const
    {
      return boost::filesystem::exists(path());
    }

    std::ostream &operator<<(std::ostream &os, const base &loc)
    {
      os << loc.path().string();
      return os;
    }
  }
}
