#include <pepper/appfw/cli/service/exitcode/impl.hpp>

namespace pepper { namespace appfw { namespace cli { namespace service { namespace exitcode {

  impl::impl(pepper::optional::object<int> &code) : _code( code )
  {
    // DO NOTHING
  }

  void impl::set(const int &num)
  {
    _code = num;
  }

} } } } }


