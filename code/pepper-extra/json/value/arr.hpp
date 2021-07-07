#ifndef __PEPPER_JSON_ARR_VALUE_H__
#define __PEPPER_JSON_ARR_VALUE_H__

#include <vector>

namespace pepper { namespace json {
  
  template <typename T> class arr : public std::vector<T>
  {
    public:
      arr() = default;
      virtual ~arr() = default;
  };

} }

#endif
