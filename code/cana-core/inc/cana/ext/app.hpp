#ifndef __CANA_EXT_APP_H__
#define __CANA_EXT_APP_H__

#include <cana/proc/info.hpp>

namespace cana { namespace ext {

  struct app
  {
    app() = default;
    virtual ~app() = default;

    virtual void notifyProcessEnter(const cana::proc::info &) = 0;
    virtual void notifyProcessLeave(const cana::proc::info &) = 0;
  };

} }

#endif
