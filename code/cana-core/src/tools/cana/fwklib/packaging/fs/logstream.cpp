#include "logstream.hpp"

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  logstream::logstream(const std::string &name) : _point{name}
  {
    // DO NOTHING
  }

  void logstream::fatal(const std::string &message)
  {
    _point.fatal(message);
  }

  void logstream::error(const std::string &message)
  {
    _point.error(message);
  }

  void logstream::warn(const std::string &message)
  {
    _point.warn(message);
  }

  void logstream::info(const std::string &message)
  {
    _point.info(message);
  }

  void logstream::debug(const std::string &message)
  {
    _point.debug(message);
  }

  void logstream::trace(const std::string &message)
  {
    _point.trace(message);
  }

} } } }
