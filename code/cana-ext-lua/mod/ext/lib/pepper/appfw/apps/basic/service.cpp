#include <pepper/appfw/apps/basic/service.hpp>

namespace pepper { namespace appfw { namespace apps { namespace basic {

  service::service(appfw::service::desc &srv) : _srv(srv)
  {
    // DO NOTHING
  }

  appfw::service::cmdline::desc &service::cmdline(void)
  {
    return _srv.cmdline();
  }

} } } }
