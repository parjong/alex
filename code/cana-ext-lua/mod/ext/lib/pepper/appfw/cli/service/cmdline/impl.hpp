#ifndef __PEPPER_APPFW_CLI_SERVICE_CMDLINE_IMPL_H__
#define __PEPPER_APPFW_CLI_SERVICE_CMDLINE_IMPL_H__

#include <pepper/appfw/service/cmdline/desc.hpp>
#include <pepper/appfw/cli/cursor.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service { namespace cmdline {

  struct impl : public appfw::service::cmdline::desc
  {
    private:
      cli::cursor &_args;

    public:
      virtual optional::object<std::string> access(unsigned off) const;

    public:
      impl(cli::cursor &args);
  
    public:
      virtual ~impl(void) = default;
  };

} } } } }

#endif
