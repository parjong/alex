#ifndef __PEPPER_APPFW_APPS_BASIC_DESC_H__
#define __PEPPER_APPFW_APPS_BASIC_DESC_H__

#include <pepper/appfw/app/desc.hpp>
#include <pepper/appfw/apps/basic/service.hpp>

namespace pepper { namespace appfw { namespace apps { namespace basic {

  class desc : public app::desc
  {
    public:
      desc() = default;
      virtual ~desc() = default;

    public:
      virtual void enroll(app::option::set &);

    private:
      virtual void enroll(app::command::set &) final;

    private:
      virtual void invoke(appfw::service::desc &) final;

    public:
      virtual int  main(basic::service &) = 0;
  };

} } } }

#endif
