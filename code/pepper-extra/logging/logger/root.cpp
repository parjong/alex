#include "pepper/logging/logger/root.hpp"

namespace pepper { namespace logging {
 
  root::root() : _logger{ nullptr }
  {
    // DO NOTHING
  }
      
  log4cxx::LoggerPtr root::ptr(void) 
  {
    if ( _logger == nullptr )
      _logger = log4cxx::Logger::getRootLogger();

    return _logger;
  }

  std::string root::path(void) 
  { 
    return "root";
  };

  root &root::instance(void)
  {
    static root instance{ };
    return instance;
  }

} }
