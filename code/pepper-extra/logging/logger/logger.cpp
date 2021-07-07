#include "pepper/logging/logger/logger.hpp"
#include "pepper/logging/logger/root.hpp"

namespace pepper { namespace logging {
 
  logger::logger(const std::string &name)
    : _parent( root::instance() )
    , _name{ name }
  {
    // DO NOTHING        
  }

  logger::logger(base &parent, const std::string &name)
    : _parent( parent )
    , _name{ name }
  {
    // DO NOTHING        
  }

  log4cxx::LoggerPtr logger::ptr(void) 
  { 
    if ( _logger == nullptr )    
      _logger = log4cxx::Logger::getLogger( path() );    

    return _logger; 
  }

  std::string logger::path(void) 
  { 
    return _parent.path() + "." + _name;
  };

} }
