#ifndef __CANA_BINDER_LUA_APP_H__
#define __CANA_BINDER_LUA_APP_H__

#include <cana/ext/app.hpp>
#include <cana/ext/logger.hpp>

#include <memory>
#include <string>

namespace cana { namespace binder { namespace lua {

  class app : public cana::ext::app
  {
    private:
      cana::ext::logger _logger;
      std::string _path;

    public:
      app(cana::ext::logger &&, const std::string &);
      virtual ~app() = default;

    public:
      virtual void notifyProcessEnter(const cana::proc::info &);
      virtual void notifyProcessLeave(const cana::proc::info &);
  };

} } }

#endif
