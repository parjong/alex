#ifndef __CURSOR_H__
#define __CURSOR_H__

#include "stream/base.h"

namespace tokens {
  class cursor {
    private:
      stream::base &stream_;
    public:
      cursor(stream::base &stream); 
      ~cursor() = default;

    public:
      void forward(std::size_t off);
      boost::optional<std::string> lookup(std::size_t off);
  };
}


#endif
