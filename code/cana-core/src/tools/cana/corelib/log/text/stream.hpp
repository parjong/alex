#ifndef __CANA_CORELIB_LOG_TEXT_STREAM_H__
#define __CANA_CORELIB_LOG_TEXT_STREAM_H__

#include <cana/log/level.hpp>
#include <cana/log/stream.hpp>

#include <memory>

#include "file.hpp"

namespace cana { namespace corelib { namespace log { namespace text {

  class stream : public cana::log::stream
  {
    private:
      std::shared_ptr<text::file> _file;
      cana::log::level            _level;

    public:
      stream(const std::shared_ptr<text::file> &file, const cana::log::level &level);

    public:
      virtual ~stream() = default;

    public:
      virtual cana::log::level level(void) const;

    public:
      virtual void fatal(const std::string &message);
      virtual void error(const std::string &message);
      virtual void warn(const std::string &message);
      virtual void info(const std::string &message);
      virtual void debug(const std::string &message);
      virtual void trace(const std::string &message);
  };

} } } }

#endif
