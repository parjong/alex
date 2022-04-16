#ifndef __CANA_PROC_INFO_H__
#define __CANA_PROC_INFO_H__

#include "arg.hpp"
#include "env.hpp"

#include <string>

namespace cana { namespace proc {

  struct info
  {
    info() = default;
    virtual ~info() = default;

    virtual const std::string &image(void) const = 0;

    virtual const proc::arg &arg(void) const = 0;
    virtual const proc::env &env(void) const = 0;
  };

} }

#endif
