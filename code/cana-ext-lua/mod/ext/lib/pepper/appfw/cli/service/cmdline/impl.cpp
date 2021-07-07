#include <pepper/appfw/cli/service/cmdline/impl.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service { namespace cmdline {

  impl::impl(cli::cursor &args) : _args( args )
  {
    // DO NOTHING
  }

  pepper::optional::object<std::string> impl::access(unsigned off) const
  {
    return _args.access(off);
  }

} } } } }
