#ifndef __PEPPER_BUILD_PROJECT_PATHNAME_ROOT_H__
#define __PEPPER_BUILD_PROJECT_PATHNAME_ROOT_H__

#include <pepper/pathname.hpp>

#include <string>

namespace core { namespace project { namespace pathname {

  struct manifest : public pepper::pathname::file
  {
    manifest(const boost::filesystem::path &path);
    virtual ~manifest() = default;
  };

  struct units : public pepper::pathname::dir
  {
    units(const boost::filesystem::path &path);
    virtual ~units() = default;
  };

  struct root : public pepper::pathname::dir
  {
    root(const boost::filesystem::path &path);
    virtual ~root() = default;

    pathname::manifest manifest(void) const;
    pathname::units    units(void) const;
  };

} } }

#endif
