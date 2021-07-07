#include <pepper/pathname/base.hpp>

namespace pepper { namespace pathname {

  const boost::filesystem::path &base::path(void) const
  {
    return _path;
  }

  base::base(const boost::filesystem::path &path) : _path{ path }
  {
    // DO NOTHING
  }

  dir::dir(const boost::filesystem::path &path) : base{ path }
  {
    // DO NOTHING
  }

  file::file(const boost::filesystem::path &path) : base{ path }
  {
    // DO NOTHING
  }

} }
