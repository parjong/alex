#ifndef __PEPPER_APPFW_APP_NESTED_DESC_H__
#define __PEPPER_APPFW_APP_NESTED_DESC_H__

#include <pepper/appfw/app/desc.hpp>
#include <pepper/appfw/apps/nested/command.hpp>
#include <pepper/dict.hpp>

namespace pepper { namespace appfw { namespace apps { namespace nested {

  class desc : public app::desc
  {
    public:
      desc()          = default;
      virtual ~desc() = default;

    private:
      std::map<std::string, nested::command> _commands;
    public:
      nested::command &command(const std::string &name);

    public:
      virtual void enroll(app::option::set &);
      virtual void enroll(app::command::set &);

    public:
      virtual void invoke(appfw::service::desc &);
  };

} } } }

#endif
