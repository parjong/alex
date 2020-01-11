#ifndef __CANA_EXT_STORAGE_H__
#define __CANA_EXT_STORAGE_H__

#include <string>

namespace cana { namespace ext {

  struct storage
  {
    storage()          = default;
    virtual ~storage() = default;

    virtual std::string resolve(const std::string &p) const = 0;
  };

} }

#endif
