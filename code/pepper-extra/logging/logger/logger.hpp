#ifndef __PEPPER_LOGGING_USER_LOGGER_H__
#define __PEPPER_LOGGING_USER_LOGGER_H__

#include "pepper/logging/logger/base.hpp"

namespace pepper { namespace logging {
 
  class logger : public base
  {
    private:
      base &_parent;
      const std::string _name;

    public:      
      explicit logger(const std::string &name);
      explicit logger(base &parent, const std::string &name);
      virtual ~logger() = default;

    private:
      log4cxx::LoggerPtr _logger;
    private:
      virtual log4cxx::LoggerPtr ptr(void);
      virtual std::string        path(void);
  };
    
} }

#endif
