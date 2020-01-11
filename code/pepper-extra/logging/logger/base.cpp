#include "pepper/logging/logger/base.hpp"

namespace pepper { namespace logging {
 
  void base::debug(const std::string &msg)  { LOG4CXX_DEBUG( ptr(), msg);  }
  void base::info(const std::string &msg)   { LOG4CXX_INFO( ptr(), msg);   }
  void base::warn(const std::string &msg)   { LOG4CXX_WARN( ptr(), msg);   }
  void base::error(const std::string &msg)  { LOG4CXX_ERROR( ptr(), msg);  }
 
} }
