#include "pepper/strcast.hpp"

#include <string>

namespace pepper
{

template<> int safe_strcast(const char *s, const int &v)
{
  if (s == nullptr)
  {
    return v;
  }

  return std::stoi(s);
}

} // namespace pepper
