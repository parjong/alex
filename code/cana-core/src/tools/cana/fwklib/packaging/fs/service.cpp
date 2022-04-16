#include "service.hpp"

#include "logstream.hpp"

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  service::service(const std::shared_ptr<cana::ext::package> &p, const std::shared_ptr<cana::ext::storage> &s, const std::string &logname)
  {
    _package = p;
    _storage = s;
    _logname = logname;
  }

  const std::shared_ptr<cana::ext::package> &service::package(void) const
  { 
    return _package;
  }
  
  const std::shared_ptr<cana::ext::storage> &service::storage(void) const
  { 
    return _storage;
  }

  cana::ext::logger service::logger(void) const
  {
    return std::unique_ptr<cana::ext::logstream>{
      new fs::logstream{_logname}
    };
  }

} } } }
