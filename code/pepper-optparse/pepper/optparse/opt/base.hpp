#ifndef __PEPPER_OPTPARSE_OPT_BASE_H__
#define __PEPPER_OPTPARSE_OPT_BASE_H__

#include <pepper/stream.hpp>

#include <string>

namespace pepper { namespace optparse { namespace opt { 
 
  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual bool take(pepper::stream::base<std::string> &s) = 0;
  };

} } }

#endif
