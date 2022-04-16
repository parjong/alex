#ifndef __CANA_LOG_BACKEND_H__
#define __CANA_LOG_BACKEND_H__

#include "factory.hpp"

#include <memory>

namespace cana { namespace log {

  struct backend
  {
    backend() = default;
    virtual ~backend() = default;

    virtual std::unique_ptr<factory> make(void) const = 0;
  };

} }

#endif
