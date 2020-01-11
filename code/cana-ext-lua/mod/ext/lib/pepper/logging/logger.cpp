#include "pepper/logging/logger.hpp"

namespace pepper { namespace logging {

  logger::logger(const std::string &tag)
    : _ptr{ nullptr }
  {
    _ptr = log4cxx::Logger::getLogger(tag);
  }

  logger::logger(const logger &parent, const std::string &tag)
    : _ptr{ nullptr }
  {
    std::string name{ };
    
    parent._ptr->getName( name );    
    name += ".";
    name += tag;

    _ptr = log4cxx::Logger::getLogger(name);
  }

} }
