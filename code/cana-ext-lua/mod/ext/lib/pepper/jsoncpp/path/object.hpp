#ifndef __PEPPER_JSONCPP_PATH_H__
#define __PEPPER_JSONCPP_PATH_H__

#include <pepper/jsoncpp/path/accessor.hpp>
#include <pepper/mem.hpp>

#include <string>

namespace pepper { namespace jsoncpp { namespace path {

  struct object
  {
    private:
      std::shared_ptr<path::accessor> _accessor;

    public:
      object();
      object(const std::shared_ptr<path::accessor> &accessor);
      object(const object &o);

    public:
      object named(const std::string &) const;
      object indexed(int) const;

    public:
      Json::Value &access(Json::Value &value) const;
      const Json::Value &access(const Json::Value &value) const;
  };

} } }

#endif
