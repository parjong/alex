#ifndef __STREAM_VECTOR_H__
#define __STREAM_VECTOR_H__

#include "libscan/stream/base.h"

#include <vector>

namespace tokens {
  namespace stream {
    class vector : public base {
      public:
        vector(const std::vector<std::string> &v);
        virtual ~vector() = default;

      private:
        std::vector<std::string>::const_iterator cur_;
        std::vector<std::string>::const_iterator end_;

      public:
        virtual void forward(std::size_t off);
        virtual boost::optional<std::string> lookup(std::size_t off) const;
    };
  }
}


#endif
