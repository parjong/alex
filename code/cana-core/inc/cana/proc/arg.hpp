#ifndef __CANA_PROC_ARG_H__
#define __CANA_PROC_ARG_H__

#include <functional>
#include <string>

namespace cana { namespace proc {

  struct arg
  {
    arg() = default;
    virtual ~arg() = default;

    virtual void each(const std::function<void (const std::string &)> &cb) const = 0;
  };

} }

#endif
