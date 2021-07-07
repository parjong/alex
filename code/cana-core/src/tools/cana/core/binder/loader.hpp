#ifndef __CANA_CORE_FWK_LOADER_H__
#define __CANA_CORE_FWK_LOADER_H__

#include <cana/core/binder/catalog.hpp>

namespace cana { namespace core { namespace binder {

  struct loader
  {
    loader()          = default;
    virtual ~loader() = default;

    virtual void load(core::binder::catalog &) = 0;
  };

} } }

#endif
