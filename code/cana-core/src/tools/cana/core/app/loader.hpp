#ifndef __CANA_CORE_APP_LOADER_H__
#define __CANA_CORE_APP_LOADER_H__

#include <cana/core/binder/catalog.hpp>
#include <cana/core/app/store.hpp>

namespace cana { namespace core { namespace app {

  struct loader
  {
    loader() = default;
    virtual ~loader() = default;

    virtual void load(core::app::store &, const core::binder::catalog &) = 0;
  };

} } }

#endif
