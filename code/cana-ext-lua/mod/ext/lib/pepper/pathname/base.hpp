#ifndef __PEPPER_PATHNAME_BASE_H__
#define __PEPPER_PATHNAME_BASE_H__

#include <boost/filesystem.hpp>

namespace pepper { namespace pathname {

  struct base 
  {
    private:
      boost::filesystem::path _path;
    public:
      const boost::filesystem::path &path(void) const;

    public:
      base(const boost::filesystem::path &path);

    public:
      virtual ~base() = default;
  };

  struct dir : public base
  {
    dir(const boost::filesystem::path &path);
    virtual ~dir() = default;
  };

  struct file : public base
  {
    file(const boost::filesystem::path &path); 
    virtual ~file() = default;
  };

} }

#endif
