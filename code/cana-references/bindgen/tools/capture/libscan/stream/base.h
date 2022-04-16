#ifndef __STREAM_H__
#define __STREAM_H__

#include <cstddef>
#include <string>
#include <boost/optional.hpp>

namespace tokens {
  namespace stream {
    struct base {
      base() = default;
      virtual ~base() = default;
     
      virtual void forward(std::size_t off) = 0;
      virtual boost::optional<std::string> lookup(std::size_t off) const = 0;
    };
  }
}

#endif
