#ifndef __PEPPER_JSONCPP_IMAGE_CREF_ACCESSOR_H__
#define __PEPPER_JSONCPP_IMAGE_CREF_ACCESSOR_H__

#include <pepper/jsoncpp/image/accessor.hpp>

#include <jsoncpp/json/value.h>

namespace pepper { namespace jsoncpp { namespace image { namespace cref {

  class accessor : public image::accessor
  {
    private:
      const Json::Value &_ref;

    public:
      accessor(const Json::Value &ref);

    public:
      virtual ~accessor() = default;

    private:
      virtual const Json::Value &value(void) const;
  };

} } } }

#endif
