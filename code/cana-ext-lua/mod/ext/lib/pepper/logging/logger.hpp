#ifndef __PEPPER_LOGGING_LOGGER_H__
#define __PEPPER_LOGGING_LOGGER_H__

#include <string>
#include <log4cxx/logger.h>

#include <pepper/fmt.hpp>

namespace pepper { namespace logging { 
  
  class logger
  {
    private:        
      log4cxx::LoggerPtr _ptr;

    public:
      logger(const std::string &name);
      logger(const logger &parent, const std::string &name);
    public:
      ~logger() = default;

    public:
      template <typename... Args> void trace(const Args&... args)
      {
        LOG4CXX_TRACE(_ptr, pepper::fmt::make(args...));
      }

      template <typename... Args> void debug(const Args&... args)
      {
        LOG4CXX_DEBUG(_ptr, pepper::fmt::make(args...));
      }

      template <typename... Args> void info(const Args&... args)
      {
        LOG4CXX_INFO(_ptr, pepper::fmt::make(args...));
      }

      template <typename... Args> void warn(const Args&... args)
      {
        LOG4CXX_WARN(_ptr, pepper::fmt::make(args...));
      }

      template <typename... Args> void error(const Args&... args)
      {
        LOG4CXX_ERROR(_ptr, pepper::fmt::make(args...));
      }

      template <typename... Args> inline void fatal(const Args&... args)
      {
        LOG4CXX_FATAL(_ptr, pepper::fmt::make(args...));
      }
  };

} }

#endif
