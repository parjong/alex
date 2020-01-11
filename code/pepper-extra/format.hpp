#ifndef __PEPPER_FORMAT_H__
#define __PEPPER_FORMAT_H__

#include <boost/format.hpp>

namespace pepper
{
  namespace format
  {
    void append(boost::format &fmt);

    template <typename Value, typename... Values> 
      void append(boost::format &fmt, const Value& value, const Values&...values)
    {
      fmt % value;
      append(fmt, values...);
    }
  }
}

#endif
