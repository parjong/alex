#ifndef __PEPPER_OWNED_TABLE_H__
#define __PEPPER_OWNED_TABLE_H__

#include "pepper/owned/table.hpp"

#include <string>

namespace pepper { namespace owned {
  
  template <typename V> class table 
    : public map<std::string, V> 
  {
    public:
      table() = default;
      virtual ~table() = default;
  };

} }

#endif
