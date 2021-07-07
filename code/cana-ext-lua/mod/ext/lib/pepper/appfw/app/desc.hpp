#ifndef __PEPPER_APPFW_APP_DESC_H__
#define __PEPPER_APPFW_APP_DESC_H__

#include <pepper/appfw/service/desc.hpp>

#include <pepper/appfw/app/option/set.hpp>
#include <pepper/appfw/app/command/set.hpp>

namespace pepper { namespace appfw { namespace app {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual void  enroll(app::option::set &) = 0;
    virtual void  enroll(app::command::set &) = 0;

    virtual void  invoke(service::desc &) = 0;
  };

} } }

#endif
