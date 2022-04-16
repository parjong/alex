#ifndef __PEPPER_APPFW_APP_SERVICE_DESC_H__
#define __PEPPER_APPFW_APP_SERVICE_DESC_H__

#include <pepper/appfw/service/cmdline/desc.hpp>
#include <pepper/appfw/service/exitcode/desc.hpp>

namespace pepper { namespace appfw { namespace service {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual service::cmdline::desc  &cmdline(void)  = 0;
    virtual service::exitcode::desc &exitcode(void) = 0;
  };

} } }

#endif
