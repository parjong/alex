#include "stream.hpp"

namespace cana { namespace corelib { namespace log { namespace text {

  stream::stream(const std::shared_ptr<text::file> &file, const cana::log::level &level)
  {
    _file = file;
    _level = level;
  }

  cana::log::level stream::level(void) const
  {
    return _level;
  }

  void stream::fatal(const std::string &message)
  {
    _file->write("FATAL", message);
  }

  void stream::error(const std::string &message)
  {
    _file->write("ERROR", message);
  }

  void stream::warn(const std::string &message)
  {
    _file->write("WARN", message);
  }

  void stream::info(const std::string &message)
  {
    _file->write("INFO", message);
  }

  void stream::debug(const std::string &message)
  {
    _file->write("DEBUG", message);
  }

  void stream::trace(const std::string &message)
  {
    _file->write("TRACE", message);
  }

} } } }
