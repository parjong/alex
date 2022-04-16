#ifndef __PEPPER_JSONCPP_PATH_ROOT_ACCESSOR_H__
#define __PEPPER_JSONCPP_PATH_ROOT_ACCESSOR_H__

#include <pepper/jsoncpp/path/accessor.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace root {

  class accessor : public path::accessor
  {
    public:
      accessor() = default;
      virtual ~accessor() = default;

    public:
      virtual Json::Value &access(Json::Value &value);
      virtual const Json::Value &access(const Json::Value &value) const;
  };

} } } }

#endif
