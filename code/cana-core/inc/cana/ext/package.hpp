#ifndef __CANA_EXT_PACKAGE_H__
#define __CANA_EXT_PACKAGE_H__

#include <string>

namespace cana { namespace ext {

  struct package
  {
    package()          = default;
    virtual ~package() = default;

    virtual std::string resolve(const std::string &p) const = 0;
  };

} }

#endif
