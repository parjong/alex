#ifndef __CANA_EXT_LOGGER_H__
#define __CANA_EXT_LOGGER_H__

#include "logstream.hpp"

#include <memory>
#include <string>
#include <sstream>

namespace cana { namespace ext {

  class logger
  {
    private:
      std::unique_ptr<ext::logstream> _stream;

    public:
      logger(std::unique_ptr<ext::logstream> &&stream)
      {
        _stream = std::move(stream);
      }

    public:
      logger(logger &&l)
      {
        _stream = std::move(l._stream);
      }

    public:
      ~logger() = default;

    private:
      template <typename... Args> void append(std::ostream &os, const Args&... args);

      template <typename Arg> void append(std::ostream &os, const Arg& arg)
      {
        os << arg;
      }

      template <typename Arg, typename... Args> void append(std::ostream &os, const Arg& arg, const Args&... args)
      {
        append(os, arg);
        append(os, args...);
      }

    public:
      template <typename... Args> void fatal(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->fatal(ss.str());
      }

      template <typename... Args> void error(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->error(ss.str());
      }

      template <typename... Args> void warn(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->warn(ss.str());
      }

      template <typename... Args> void info(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->info(ss.str());
      }

      template <typename... Args> void debug(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->debug(ss.str());
      }

      template <typename... Args> void trace(const Args&... args)
      {
        std::stringstream ss;
        append(ss, args...);
        _stream->trace(ss.str());
      }
  };

} }

#endif
