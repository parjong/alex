#ifndef __PEPPER_PATHNAME_SUBDIR_H__
#define __PEPPER_PATHNAME_SUBDIR_H__

#include "pepper/pathname/dir.hpp"

namespace pepper { namespace pathname {
  
  class subdir : public dir
  {
    public:
      subdir(const dir &parent, const std::string &name);
      virtual ~subdir() = default;
  };
  
} }

#endif
