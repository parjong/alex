#ifndef __PEPPER_VECTOR_STREAM_H__
#define __PEPPER_VECTOR_STREAM_H__

#include "pepper/stream/base.hpp"

#include <vector>

namespace pepper { namespace stream {

  class vector : public base 
  {
    private:
      const std::vector<std::string> &_vec;      
      std::vector<std::string>::const_iterator _cur;

    public:
      vector(const std::vector<std::string> &vector);
      virtual ~vector() = default;

    public:
      virtual boost::optional<std::string> lookup(unsigned off) const;
      virtual void forward(unsigned off);
  };

} }

#endif
