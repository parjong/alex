#ifndef __CANA_LOG_STREAM_H__
#define __CANA_LOG_STREAM_H__

#include "level.hpp"

#include <string>

namespace cana { namespace log {

  struct stream
  {
    stream()           = default;
    virtual ~stream()  = default;

    virtual log::level level(void) const = 0;

    virtual void fatal(const std::string &) = 0;
    virtual void error(const std::string &) = 0;
    virtual void warn(const std::string &) = 0;
    virtual void info(const std::string &) = 0;
    virtual void debug(const std::string &) = 0;
    virtual void trace(const std::string &) = 0;
  };

} }

#endif
