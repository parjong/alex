#ifndef __CANA_EXT_LOGSTREAM_H__
#define __CANA_EXT_LOGSTREAM_H__

#include <string>

namespace cana { namespace ext {

  struct logstream
  {
    logstream()          = default;
    virtual ~logstream() = default;

    virtual void fatal(const std::string &message)  = 0;
    virtual void error(const std::string &message)  = 0;
    virtual void warn(const std::string &message)   = 0;
    virtual void info(const std::string &message)   = 0;
    virtual void debug(const std::string &message)  = 0;
    virtual void trace(const std::string &message)  = 0;
  };

} }

#endif
