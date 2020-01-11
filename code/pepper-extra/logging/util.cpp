#include "pepper/logging/util.hpp"

#include <boost/filesystem.hpp>
#include <log4cxx/propertyconfigurator.h>

namespace pepper { namespace logging {

  void configure(void)
  {
    log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getOff());

    std::string config{  "log4cxx.ini" };

    if ( char *value = std::getenv("LOG4CXX_CFG") )
    {
      config = value;
    }

    if ( boost::filesystem::exists(config) )
      log4cxx::PropertyConfigurator::configure(config);
  }
  
} }
