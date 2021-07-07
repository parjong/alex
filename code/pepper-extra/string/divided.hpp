#ifndef __PEPPER_STRING_DIVIDED_H__
#define __PEPPER_STRING_DIVIDED_H__

#include <string>

namespace pepper { namespace string {

  class divided
  {
    private:
      std::string _left;
      std::string _right;

    public:
      divided(const std::string &s, const char d);

    public:
      const std::string &left(void) const;
      const std::string &right(void) const;
  };

} } 


#endif
