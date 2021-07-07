#include "pepper/string/divided.hpp"

namespace pepper { namespace string {

  divided::divided(const std::string &s, const char d)
  {
    std::size_t off = s.find_first_of(d);

    if ( off == std::string::npos ) 
    {
      _left = s;
    } 
    else 
    {       
      _left   = s.substr(0, off);
      _right  = s.substr(off + 1);
    }
  }

  const std::string &divided::left(void) const { return _left; }
  const std::string &divided::right(void) const { return _right; }

} }
