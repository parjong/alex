#ifndef __PEPPER_JSONCPP_PATH_INDEXED_ACCESSOR_H__
#define __PEPPER_JSONCPP_PATH_INDEXED_ACCESSOR_H__

#include <pepper/jsoncpp/path/accessor.hpp>
#include <pepper/jsoncpp/path/object.hpp>

namespace pepper { namespace jsoncpp { namespace path { namespace indexed {

  class accessor : public path::accessor
  {
    private:
      path::object _prev;
      int _offset;

    public:
      accessor(const path::object &prev, int offset);

    public:
      virtual ~accessor() = default;

    public:
      virtual Json::Value &access(Json::Value &value);
      virtual const Json::Value &access(const Json::Value &value) const;
  };

} } } }

#endif
