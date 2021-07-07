#ifndef __CANA_PROC_ENV_H__
#define __CANA_PROC_ENV_H__

#include <functional>
#include <string>

namespace cana { namespace proc {

  struct env
  {
    env() = default;
    virtual ~env() = default;

    virtual bool lookup(const std::string &k, const std::function<void (const std::string &v)> &cb) const = 0;
    virtual void each(const std::function<void (const std::string &k, const std::string &v)> &cb) const = 0;
  };

} }

#endif
