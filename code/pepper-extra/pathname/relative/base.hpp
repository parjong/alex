#ifndef __PEPPER_PATHNAME_RELATIVE_BASE_H__
#define __PEPPER_PATHNAME_RELATIVE_BASE_H__

#include <boost/filesystem.hpp>

#include <ostream>

namespace pepper { namespace pathname { namespace relative {
  
  class base
  {
    private:
      boost::filesystem::path _path;

    public:
      base(const boost::filesystem::path &path);
      virtual ~base() = default;

    public:
      const boost::filesystem::path &path(void) const;
  };   

  std::ostream &operator<<(std::ostream &os, const base &pn);

  class dir : public base
  {
    public:
      dir(const boost::filesystem::path &path);
      virtual ~dir() = default;
  };

  class file : public base
  {
    public:
      file(const boost::filesystem::path &path);
      virtual ~file() = default;
  };

} } }

#endif
