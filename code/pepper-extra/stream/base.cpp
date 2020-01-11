#include "pepper/stream/base.hpp"

namespace pepper { namespace stream {

  boost::optional<std::string> base::next(void) 
  {
    auto res = lookup(0);
    forward(1);
    return res;
  }

  void base::iter(std::function<void (const std::string &)> fn)
  {
    for ( ; (bool) lookup(0); forward(1) )
    {
      fn( lookup(0).get() );
    }
  }

} }
