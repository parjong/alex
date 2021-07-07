#ifndef __PEPPER_APPFW_CLI_HOST_H__
#define __PEPPER_APPFW_CLI_HOST_H__

#include <pepper/appfw/app/desc.hpp>
#include <pepper/appfw/cli/args/desc.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace appfw { namespace cli {

  class host
  {
    private:
      std::shared_ptr<pepper::appfw::app::desc> _app;

    public:
      host(const std::shared_ptr<pepper::appfw::app::desc> &app);
      ~host() = default;
    
    public:
      int run(const pepper::appfw::cli::args::desc &args);
  };

} } }

#endif
