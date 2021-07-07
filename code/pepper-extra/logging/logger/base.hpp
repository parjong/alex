#ifndef __PEPPER_LOGGING_BASE_LOGGER_H__
#define __PEPPER_LOGGING_BASE_LOGGER_H__

#include <log4cxx/logger.h>

#include "pepper/format.hpp"

namespace pepper { namespace logging {
 
  class base
  {
    public:
      base() = default;
      virtual ~base() = default;

    public:
      virtual log4cxx::LoggerPtr ptr(void) = 0;
      virtual std::string path(void) = 0;

    public:
      void debug(const std::string &msg);

      template <typename... Values> 
        void debug(const std::string &fmtstr, const Values&... values)
        {
          boost::format fmt(fmtstr);
          pepper::format::append(fmt, values...);
          debug(boost::str(fmt));
        }

    public:
      void info(const std::string &msg);

      template <typename... Values> 
        void info(const std::string &fmtstr, const Values&... values)
        {
          boost::format fmt(fmtstr);
          pepper::format::append(fmt, values...);
          info(boost::str(fmt));
        }

    public:
      void warn(const std::string &fmt);

      template <typename... Values> 
        void warn(const std::string &fmtstr, const Values&... values)
        {
          boost::format fmt(fmtstr);
          pepper::format::append(fmt, values...);
          warn(boost::str(fmt));
        }

    public:
      void error(const std::string &fmt);

      template <typename... Values> 
        void error(const std::string &fmtstr, const Values&... values)
        {
          boost::format fmt(fmtstr);
          pepper::format::append(fmt, values...);
          warn(boost::str(fmt));
        }
  };
    
} }

#endif
