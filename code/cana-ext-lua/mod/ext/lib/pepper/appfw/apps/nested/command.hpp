#ifndef __PEPPER_APPFW_APPS_NESTED_COMMAND_H__
#define __PEPPER_APPFW_APPS_NESTED_COMMAND_H__

#include <pepper/appfw/app/command/set.hpp>
#include <pepper/mem.hpp>

#include <string>

namespace pepper { namespace appfw { namespace apps { namespace nested {

  class command
  {
    private:
      std::shared_ptr<app::desc> _app;

    public:
      command()  = default;
      ~command() = default;
 
    public:
      command &set(const std::shared_ptr<app::desc> &app);

    public:
      void enroll(app::command::set &s, const std::string &name);
  };

} } } }

#endif
