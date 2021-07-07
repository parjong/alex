#include <pepper/fmt/value.hpp>

namespace pepper { namespace fmt {

  std::ostream &operator<<(std::ostream &os, const base &o)
  {
    return o.output(os);
  }

} }
