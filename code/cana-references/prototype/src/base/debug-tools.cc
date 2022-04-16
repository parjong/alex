#include "debug-tools.h"

#include <unistd.h>

#include <log4cxx/helpers/exception.h>
#include <log4cxx/propertyconfigurator.h>

#include <memory>

namespace debug
{
  logger::logger() 
    : name_("R")
  { 
    ptr_  = log4cxx::Logger::getLogger( name_);    
  }

  logger::logger(const logger& parent, const std::string& tag)
    : name_( parent.get_name() + "." + tag )
  {
    ptr_  = log4cxx::Logger::getLogger( name_ );
  }

  log4cxx::LoggerPtr& logger::get_ptr(void) { return ptr_; }

  const std::string& logger::get_name(void) const { return name_; }

  logger logger::get_child(const std::string& tag) const 
  { 
    return logger(*this, tag); 
  }

  logger& logger::instance(void) 
  {
    static std::unique_ptr<logger> ptr( new logger() );

    return *ptr;
  }

  void manager::init(void)
  {
    char *filename = getenv("BC_DEBUG_CFG");

    try
    {    
      if ( filename != nullptr ) 
      {
        log4cxx::PropertyConfigurator::configure( filename );

        log4cxx::MDC::put("pid", std::to_string( getpid()) );
        return;
      }
    }
    catch ( log4cxx::helpers::Exception& e )
    {
      // DO NOTHING    
    }

    log4cxx::Logger::getRootLogger()->setLevel( log4cxx::Level::getOff() );
  }
}
