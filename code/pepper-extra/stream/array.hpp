#ifndef __PEPPER_STREAM_ARRAY_H__
#define __PEPPER_STREAM_ARRAY_H__

#include "pepper/stream/base.hpp"

namespace pepper { namespace stream {

  class array : public base
  {
    private:
      int argc_;
      char **argv_;

    private:
      int curr_; // Current offset

    public:
      array(int argc, char **argv);
      virtual ~array() = default;

    public:
      virtual boost::optional<std::string> lookup(unsigned off) const;
      virtual void forward(unsigned off);
  };

} }

#endif
