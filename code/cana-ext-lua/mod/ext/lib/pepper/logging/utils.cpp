#include "pepper/logging/utils.hpp"

#include <boost/filesystem.hpp>

#include <log4cxx/propertyconfigurator.h>

namespace pepper { namespace logging {

  void configure(void)
  {
    // Turns off by default
    log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getOff());
    
    if ( boost::filesystem::exists("log4cxx.ini") )
    {
      // Read log4cxx.ini if it exists
      log4cxx::PropertyConfigurator::configure("log4cxx.ini");
    }
  }

} }
