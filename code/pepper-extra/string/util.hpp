#ifndef __PEPPER_STRING_UTIL_H__
#define __PEPPER_STRING_UTIL_H__

#include <string>

namespace pepper { namespace string {

  struct util 
  {
    static std::string lower(const std::string &from);
    static std::string upper(const std::string &from);
    static std::string camel(const std::string &from);
  };

} } 

#endif
