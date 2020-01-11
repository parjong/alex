#ifndef __PEPPER_JSONCPP_IMAGE_VALUE_ACCESSOR_H__
#define __PEPPER_JSONCPP_IMAGE_VALUE_ACCESSOR_H__

#include <pepper/jsoncpp/image/accessor.hpp>
#include <pepper/jimage.hpp>

#include <jsoncpp/json/value.h>
#include <istream>

namespace pepper { namespace jsoncpp { namespace image { namespace value {

  class accessor : public image::accessor
  {
    private:
      Json::Value _value;

    public:
      accessor(std::istream &is);

    public:
      virtual ~accessor() = default;

    private:
      virtual const Json::Value &value(void) const;
  };

} } } }

#endif
