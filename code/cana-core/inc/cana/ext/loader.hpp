#ifndef __CANA_EXT_LOADER_H__
#define __CANA_EXT_LOADER_H__

#include "app.hpp"
#include "service.hpp"

#include <memory>

namespace cana { namespace ext {

  struct loader
  {
    loader() = default;
    virtual ~loader() = default;

    virtual std::unique_ptr<ext::app> load(const ext::service &) const = 0;
  };

} }

#endif
