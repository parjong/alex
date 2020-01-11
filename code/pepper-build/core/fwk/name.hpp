#ifndef __PEPPER_BUILD_CORE_FWK_NAME_H__
#define __PEPPER_BUILD_CORE_FWK_NAME_H__

#include <pepper/attr.hpp>

namespace core { namespace fwk {

  struct name 
  {
    pepper::attr::value::reader<std::string> string;

    name(const std::string &s) : string{ s } 
    {
      // DO NOTHING
    }

    ~name() = default;
  };

} }

#endif
