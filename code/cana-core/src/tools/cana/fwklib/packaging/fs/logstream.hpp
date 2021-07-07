#ifndef __CANA_FWKLIB_PACKAGING_FS_LOGSTREAM_H__
#define __CANA_FWKLIB_PACKAGING_FS_LOGSTREAM_H__

#include <cana/ext/logstream.hpp>

#include <cana/logging/point.hpp>

namespace cana { namespace fwklib { namespace packaging { namespace fs {

  class logstream : public cana::ext::logstream
  {
    private:
      cana::logging::point _point;

    public:
      logstream(const std::string &name);

    public:
      virtual ~logstream() = default;

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
