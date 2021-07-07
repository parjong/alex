#ifndef __PEPPER_LOGGING_MESSAGE_TRACE_H__
#define __PEPPER_LOGGING_MESSAGE_TRACE_H__

#include <pepper/logging.hpp>

namespace pepper { namespace logging { namespace message {

  class trace
  {
    private:
      pepper::logging::logger &_log;

    public:
      trace(pepper::logging::logger &log) : _log( log )
      {
        _log.trace( "enter" );
      }

      ~trace()
      {
        _log.trace( "leave" );
      }
  };

} } }

#endif
