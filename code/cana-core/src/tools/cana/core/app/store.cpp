#include "store.hpp"

#include <algorithm>

namespace cana { namespace core { namespace app {

  void store::add(app::tracker &&plugin)
  {
    _plugins.emplace_back(std::move(plugin));
  }

  void store::each(const std::function<void (app::tracker &)> &fn)
  {
    std::for_each(_plugins.begin(), _plugins.end(), fn);
  }

} } }
