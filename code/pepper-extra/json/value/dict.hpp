#ifndef __PEPPER_JSON_DICT_VALUE_H__
#define __PEPPER_JSON_DICT_VALUE_H__

#include <string>
#include <map>

namespace pepper { namespace json {
  
  template <typename T> class dict : public std::map<std::string, T>
  {
    public:
      dict() = default;
      virtual ~dict() = default;
  };

} }

#endif
