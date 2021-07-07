#include "arg.hpp"

#include <algorithm>

namespace cana { namespace rt { namespace preload {

  arg::arg(char **argv)
  {
    for (char **cur = argv; *cur; ++cur)
    {
      _vec.emplace_back(*cur);
    }
  }

  void arg::each(const std::function<void (const std::string &)> &cb) const
  {
    std::for_each(_vec.begin(), _vec.end(), cb);
  }

} } }
