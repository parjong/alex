#ifndef __CANA_RT_PRELOAD_ARG_H__
#define __CANA_RT_PRELOAD_ARG_H__

#include <cana/proc/arg.hpp>

#include <string>
#include <vector>

namespace cana { namespace rt { namespace preload {

  class arg : public cana::proc::arg
  {
    private:
      std::vector<std::string> _vec;

    public:
      arg(char **argv);

    public:
      virtual ~arg() = default;

    public:
      virtual void each(const std::function<void (const std::string &)> &cb) const;
  };

} } }

#endif
