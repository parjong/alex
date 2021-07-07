#ifndef __PEPPER_JSONCPP_PATH_ACCESSOR_H__
#define __PEPPER_JSONCPP_PATH_ACCESSOR_H__

#include <jsoncpp/json/value.h>

namespace pepper { namespace jsoncpp { namespace path {

  struct accessor
  {
    accessor() = default;
    virtual ~accessor() = default;

    virtual Json::Value &access(Json::Value &) = 0;
    virtual const Json::Value &access(const Json::Value &) const = 0;
  };

} } }

#endif
