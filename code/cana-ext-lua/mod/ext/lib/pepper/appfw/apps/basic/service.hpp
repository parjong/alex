#ifndef __PEPPER_APPFW_APPS_BASIC_SERVICE_H__
#define __PEPPER_APPFW_APPS_BASIC_SERVICE_H__

#include <pepper/appfw/service/desc.hpp>

namespace pepper { namespace appfw { namespace apps { namespace basic {

  struct service
  {
    private:
      appfw::service::desc &_srv;

    public:
      service(appfw::service::desc &srv);

    public:
      ~service() = default;

    public:
      appfw::service::cmdline::desc &cmdline(void);
  };

} } } }

#endif
