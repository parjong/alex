#ifndef __PEPPER_JSONCPP_PATH_NAMED_ACCESSOR_H__
#define __PEPPER_JSONCPP_PATH_NAMED_ACCESSOR_H__

#include <pepper/jsoncpp/path/accessor.hpp>
#include <pepper/jsoncpp/path/object.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace named {

  class accessor : public path::accessor
  {
    private:
      path::object _prev;
      std::string  _name;

    public:
      accessor(const path::object &prev, const std::string &name);

    public:
      virtual ~accessor() = default;

    public:
      virtual Json::Value &access(Json::Value &value);
      virtual const Json::Value &access(const Json::Value &value) const;
  };

} } } }

#endif
