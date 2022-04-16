#include "pepper/exec.hpp"
#include "pepper/log.hpp"

#include "pepper/logging.hpp"

namespace pepper { namespace exec {

  pepper::logging::logger command::_log{ pepper::log, "exec.command" };

  command::command(const std::string &exe)
    : _exe{ exe }
  {
    // DO NOTHING
  }

  void command::append(const std::string &arg)
  {
    _args.push_back(arg);
  }

  bool command::run(void) const
  {
    static pepper::logging::logger logger{ _log, __func__ };

    std::string cmdline;

    cmdline += _exe;

    for (auto &arg : _args) 
    {
      cmdline += " ";
      cmdline += arg;
    }

    logger.info( "invoke '%s'", cmdline );

    int status = system( cmdline.c_str() );

    return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
  }

} }
