#ifndef __PEPPER_STREAM_BASE_H__
#define __PEPPER_STREAM_BASE_H__

#include <string>
#include <functional>

#include <boost/optional.hpp>

namespace pepper { namespace stream {

  class base 
  {
    public:
      base() = default;
      virtual ~base() = default;

    public:
      virtual boost::optional<std::string> lookup(unsigned off) const = 0; 
      virtual void forward(unsigned off) = 0;

    public:
      boost::optional<std::string> next(void);

    public:
      void iter(std::function<void (const std::string &)> fn);
  };

} }

#endif
