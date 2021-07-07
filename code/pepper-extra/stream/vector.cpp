#include "pepper/stream/vector.hpp"

namespace pepper { namespace stream {

  vector::vector(const std::vector<std::string> &vec)
    : _vec(vec), _cur{ vec.begin() }
  {
    // DO NOTHING
  }

  boost::optional<std::string> vector::lookup(unsigned off) const 
  {
    auto it = _cur + off;

    if ( it >= _vec.end() ) 
      return boost::none;

    return *it;
  }

  void vector::forward(unsigned off) 
  {
    _cur += off;
  }

} }
