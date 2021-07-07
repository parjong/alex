#ifndef __PEPPER_APPFW_CLI_SERVICE_IMPL_H__
#define __PEPPER_APPFW_CLI_SERVICE_IMPL_H__

#include <pepper/appfw/service/desc.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service {

  struct impl : public pepper::appfw::service::desc
  {
    private:
      appfw::service::exitcode::desc &_code;
      appfw::service::cmdline::desc  &_cmdline;

    public:
      virtual pepper::appfw::service::cmdline::desc &cmdline(void);
      virtual pepper::appfw::service::exitcode::desc &exitcode(void);

    public:
      impl(appfw::service::exitcode::desc &code, appfw::service::cmdline::desc &cmdline);

    public:
      virtual ~impl() = default;
  };

} } } }

#endif
