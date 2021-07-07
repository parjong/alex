#include "pepper/stream/array.hpp"

namespace pepper { namespace stream {

  array::array(int argc, char **argv) 
    : argc_(argc), argv_(argv), curr_(0)
  {
    // DO NOTHING
  }

  boost::optional<std::string> array::lookup(unsigned off) const 
  {
    unsigned ind = curr_ + off;

    if ( ind >= argc_ ) 
      return boost::none;

    return std::string(argv_[ind]);
  }

  void array::forward(unsigned off) 
  {
    curr_ += off;
  }

} }
