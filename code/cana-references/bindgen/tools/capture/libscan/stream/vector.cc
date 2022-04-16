#include "libscan/stream/vector.h"

namespace tokens {
  namespace stream {
    vector::vector(const std::vector<std::string> &v) 
      : cur_(v.begin()), end_(v.end())
    {
      // DO NOTHING
    }        
  
    boost::optional<std::string> vector::lookup(std::size_t off) const {
      if ( cur_ + off >= end_ ) {
        return boost::none;
      }

      return *(cur_ + off);
    }

    void vector::forward(std::size_t off) {
      cur_ += off;
    }        
  }
}

