#ifndef __CANA_CORE_APP_STORE_H__
#define __CANA_CORE_APP_STORE_H__

#include <cana/core/app/tracker.hpp>

#include <functional>
#include <vector>

namespace cana { namespace core { namespace app {

  class store
  {
    private:
      std::vector<app::tracker> _plugins;

    public:
      void add(app::tracker &&plugin);

    public:
      void each(const std::function<void (app::tracker &)> &fn);
  };

} } }

#endif
