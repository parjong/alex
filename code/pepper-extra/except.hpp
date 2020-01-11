#ifndef __PEPPER_EXCEPT_H__
#define __PEPPER_EXCEPT_H__

#include "pepper/format.hpp"

#include <stdexcept>

namespace pepper
{
  template <typename... Values> 
    void throw_exn(const std::string &fmtstr, const Values&... values)
  {
    // DO NOTHING;
    boost::format fmt(fmtstr);
    pepper::format::append(fmt, values...);        
    throw std::runtime_error( boost::str(fmt) );
  }  
}

#endif
