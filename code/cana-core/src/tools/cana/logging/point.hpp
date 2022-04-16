#ifndef __CANA_LOGGING_POINT_H__
#define __CANA_LOGGING_POINT_H__

#include "manager.hpp"

#include <sstream>

namespace cana { namespace logging {

  class point
  {
    private:
      std::string _name;

    private:
      std::unique_ptr<log::stream> _stream;
      log::level                   _level;

    public:
      point(const std::string &name);

    public:
      ~point();

    public:
      void reset(void);

    private:
      void ensure(void);

    private:
      template <typename... Args> void append(std::ostream &os, Args&... args);

      template <typename Arg> void append(std::ostream &os, Arg& arg)
      {
        os << arg;
      }

      template <typename Arg, typename... Args> void append(std::ostream &os, Arg& arg, Args&... args)
      {
        append(os, arg);
        append(os, args...);
      }

    public:
      template <typename... Args> void fatal(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_FATAL)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->fatal(ss.str());
        }
      }

      template <typename... Args> void error(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_ERROR)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->warn(ss.str());
        }
      }

      template <typename... Args> void warn(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_WARN)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->warn(ss.str());
        }
      }

      template <typename... Args> void info(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_INFO)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->info(ss.str());
        }
      }

      template <typename... Args> void debug(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_DEBUG)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->debug(ss.str());
        }
      }

      template <typename... Args> void trace(Args&... args)
      {
        ensure();

        if (_level & cana::log::BM_TRACE)
        {
          std::stringstream ss;
          append(ss, args...);
          _stream->trace(ss.str());
        }
      }
  };

} }

#endif
