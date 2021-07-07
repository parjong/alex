#ifndef __CANA_RT_PRELOAD_ENV_H__
#define __CANA_RT_PRELOAD_ENV_H__

#include <cana/proc/env.hpp>
#include <map>

namespace cana { namespace rt { namespace preload {

  class env : public cana::proc::env
  {
    private:
      std::map<std::string, std::string> _content;

    public:
      env(char **envp);

    public:
      virtual ~env() = default;

    public:
      virtual bool lookup(const std::string &k, const std::function<void (const std::string &)> &cb) const;
      virtual void each(const std::function<void (const std::string &k, const std::string &v)> &cb) const;
  };

} } }

#endif
