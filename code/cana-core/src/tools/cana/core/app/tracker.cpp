#include "tracker.hpp"

namespace cana { namespace core { namespace app {

  tracker::tracker()
  {
    // DO NOTHING
  }

  tracker::tracker(std::unique_ptr<cana::ext::app> &&app)
  {
    _app = std::move(app);
  }

  tracker::tracker(tracker &&o)
  {
    _app = std::move(o._app);
  }

  tracker &tracker::operator=(tracker &&rhs)
  {
    _app = std::move(rhs._app);
  }

  void tracker::notifyProcessEnter(const cana::proc::info &pi)
  {
    _app->notifyProcessEnter(pi);
  }

  void tracker::notifyProcessLeave(const cana::proc::info &pi)
  {
    _app->notifyProcessLeave(pi);
  }

} } }
