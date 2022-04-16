#ifndef __PEPPER_APPFW_CLI_UNIT_H__
#define __PEPPER_APPFW_CLI_UNIT_H__

#include <pepper/appfw/app/desc.hpp>
#include <pepper/collection.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace appfw { namespace cli {

  class unit
  {
    private:
      std::shared_ptr<pepper::appfw::app::desc> _app;

    public:
      unit(const std::shared_ptr<pepper::appfw::app::desc> &app);

    public:
      pepper::appfw::app::desc &app(void);

    public:
      pepper::optional::object<int> invoke(pepper::collection::cursor::bean<std::string> &cur);

    public:
      void usage(std::ostream &os);

    public:
      pepper::maybe::object<std::shared_ptr<pepper::appfw::app::desc>> lookup(const std::string &tag);
  };

} } }

#endif
