#ifndef __PEPPER_BUILD_FWK_TABLE_H__
#define __PEPPER_BUILD_FWK_TABLE_H__

#include <core/fwk/base.hpp>

#include <map>
#include <string>

namespace core { namespace fwk {

  struct table : std::map<std::string, fwk::base *>
  {
    table() = default;
    virtual ~table() = default;
  };


} }

#endif
