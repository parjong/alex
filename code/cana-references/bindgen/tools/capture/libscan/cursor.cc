#include "cursor.h"

namespace tokens {
  cursor::cursor(stream::base &stream) : stream_(stream) {
    // DO NOTHING
  }

  boost::optional<std::string> cursor::lookup(std::size_t off) { 
    return stream_.lookup(off); 
  }

  void cursor::forward(std::size_t off) { 
    return stream_.forward(off); 
  }    
}


