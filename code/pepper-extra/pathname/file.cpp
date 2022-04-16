#include "pepper/pathname/file.hpp"

#include <fstream>

namespace pepper { namespace pathname {

  file::file(const boost::filesystem::path &path) 
    : base{ path }
  {
    // DO NOTHING
  }

  void file::create(void) const
  {
    auto fn = [](std::ostream &os)
    {
      return;
    };

    create(fn);
  }

  void file::create(std::function<void (std::ostream &)> fn) const
  {
    std::ofstream os(path().string(), std::ofstream::out);

    fn(os);
  }

  void file::create(std::function<void (FILE *)> fn) const
  {
    FILE *fp = fopen(path().string().c_str(), "w");

    fn(fp);

    fclose(fp);
  }

  void file::open(std::function<void (std::istream &)> fn) const
  {
    std::ifstream is(path().string());

    fn(is);
  }

  void file::remove(void) const
  {
    boost::filesystem::remove( path() );
  }

} }
