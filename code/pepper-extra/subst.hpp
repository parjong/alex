#ifndef __PEPPER_SUBST_H__
#define __PEPPER_SUBST_H__

#include "pepper/dict.hpp"
#include "pepper/logging/logger.hpp"

namespace pepper
{  
  class subst
  {
    private:
      static pepper::logging::logger __log__;

    public:
      subst(const pepper::dict::base &dict) : _dict(dict) 
      {
        // DO NOTHING
      }
      ~subst() = default;

    private:
      const pepper::dict::base &_dict;

    public:
      std::string rewrite(const std::string &from) const;
  };
}
#endif
