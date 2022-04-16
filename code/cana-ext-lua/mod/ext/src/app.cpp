#include "app.hpp"

#include <pepper/interop.hpp>
#include <pepper/fun.hpp>

#include <fstream>

using namespace std::placeholders;

namespace {

  int debug(cana::ext::logger &log, pepper::interop::lua51::stack::object &s)
  {
    log.debug(s.pop<std::string>());
    return 0;
  }

  int get_image(const cana::proc::info &pi, pepper::interop::lua51::stack::object &s)
  {
    s.push<std::string>(pi.image());
    return 1;
  }

}

namespace cana { namespace binder { namespace lua {

  app::app(cana::ext::logger &&logger, const std::string &path) : _logger{std::move(logger)}, _path{path}
  {
    // DO NOTHING
  }

  void app::notifyProcessEnter(const cana::proc::info &pi)
  {
    // DO NOTHING
  }

  void app::notifyProcessLeave(const cana::proc::info &pi)
  {
    pepper::interop::lua51::runtime rt;

    rt.binder().push(std::bind(::debug, std::ref(_logger), _1));
    rt.heap().store("debug");

    rt.binder().push(std::bind(::get_image, std::cref(pi), _1));
    rt.heap().store("get_image");

    _logger.info("load a LUA script from '", _path, "'");

    std::ifstream ifs{_path};
    pepper::interop::lua51::code::stream::loader code{ifs};

    rt.load(code);
    rt.eval();
  }

} } }
