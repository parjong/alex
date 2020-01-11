#ifndef __UNIT_PATHNAME_ROOT_H__
#define __UNIT_PATHNAME_ROOT_H__

#include <pepper/pathname.hpp>

namespace core { namespace unit { namespace pathname {

  struct manifest : public pepper::pathname::file
  {
    manifest(const boost::filesystem::path &path);
    virtual ~manifest() = default;
  };

  struct root : public pepper::pathname::dir
  {
    root(const boost::filesystem::path &path);
    virtual ~root() = default;

    pathname::manifest manifest(void) const;
  };

} } }

#endif
