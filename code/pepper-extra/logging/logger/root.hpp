#ifndef __PEPPER_LOGGING_ROOT_LOGGER_H__
#define __PEPPER_LOGGING_ROOT_LOGGER_H__

#include "pepper/logging/logger/base.hpp"

namespace pepper { namespace logging {
 
  class root : public base
  {
    public:
      root();
      virtual ~root() = default;

    private:
      log4cxx::LoggerPtr _logger;
    public:
      virtual log4cxx::LoggerPtr ptr(void);
      virtual std::string        path(void);

    public:
      static root &instance(void);
  };

} }

#endif
