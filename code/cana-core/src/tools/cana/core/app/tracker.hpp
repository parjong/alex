#ifndef __CANA_CORE_APP_TRACKER_H__
#define __CANA_CORE_APP_TRACKER_H__

#include <cana/ext/app.hpp>

#include <memory>

namespace cana { namespace core { namespace app {

  class tracker
  {
    private:
      std::unique_ptr<cana::ext::app> _app;

    public:
      tracker();
      tracker(std::unique_ptr<cana::ext::app> &&);
      tracker(tracker &&o);

    public:
      ~tracker() = default;

    public:
      tracker &operator=(tracker &&);

    public:
      void notifyProcessEnter(const cana::proc::info &);
      void notifyProcessLeave(const cana::proc::info &);
  };

} } }

#endif
