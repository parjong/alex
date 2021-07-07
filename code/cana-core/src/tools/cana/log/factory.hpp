#ifndef __CANA_LOG_FACTORY_H__
#define __CANA_LOG_FACTORY_H__

#include "stream.hpp"

#include <string>
#include <memory>

namespace cana { namespace log {

  struct factory
  {
    factory()           = default;
    virtual ~factory()  = default;

    virtual std::unique_ptr<stream> make(const std::string &name) const = 0;
  };

} }

#endif
