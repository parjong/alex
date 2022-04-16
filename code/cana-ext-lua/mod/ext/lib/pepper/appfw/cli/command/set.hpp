#ifndef __PEPPER_APPFW_CLI_COMMAND_SET_H__
#define __PEPPER_APPFW_CLI_COMMAND_SET_H__

#include <pepper/appfw/app/command/set.hpp>

#include <pepper/attr.hpp>
#include <pepper/dict.hpp>

namespace pepper { namespace appfw { namespace cli { namespace command {

  class set : public pepper::appfw::app::command::set
  {
    public:
      typedef pepper::dict::object<std::string, std::shared_ptr<pepper::appfw::app::desc>> dict;

    private:
      pepper::attr::ref::accessor<dict> _dict;

    public:
      virtual void enroll( const std::string &name, const std::shared_ptr<pepper::appfw::app::desc> &app );

    public:
      set(dict &d);

    public:
      virtual ~set() = default;
  };

} } } }

#endif
