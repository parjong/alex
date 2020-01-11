#include <pepper/appfw/cli/service/impl.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service {

  impl::impl(pepper::appfw::service::exitcode::desc &code, pepper::appfw::service::cmdline::desc &cmdline) 
    : _code( code ), _cmdline( cmdline )
  {
    // DO NOTHING
  }

  pepper::appfw::service::cmdline::desc &impl::cmdline(void)
  {
    return _cmdline;
  }

  pepper::appfw::service::exitcode::desc &impl::exitcode(void)
  {
    return _code;
  }

} } } }


