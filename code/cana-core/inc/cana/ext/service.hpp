#ifndef __CANA_EXT_SERVICE_H__
#define __CANA_EXT_SERVICE_H__

#include "package.hpp"
#include "storage.hpp"
#include "logger.hpp"

#include <memory>

namespace cana { namespace ext {

  struct service
  {
    service() = default;
    virtual ~service() = default;

    virtual const std::shared_ptr<ext::package> &package(void) const = 0;
    virtual const std::shared_ptr<ext::storage> &storage(void) const = 0;
    virtual ext::logger logger(void) const = 0;
  };

} }

#endif
