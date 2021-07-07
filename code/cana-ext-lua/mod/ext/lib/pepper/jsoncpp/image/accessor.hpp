#ifndef __PEPPER_JSONCPP_IMAGE_ACCESSOR_H__
#define __PEPPER_JSONCPP_IMAGE_ACCESSOR_H__

#include <pepper/jimage.hpp>
#include <pepper/mem.hpp>

#include <jsoncpp/json/value.h>

#include <istream>

namespace pepper { namespace jsoncpp { namespace image {

  class accessor : public jimage::accessor
  {
    public:
      accessor() = default;

    public:
      virtual ~accessor() = default;

    private:
      virtual const Json::Value &value(void) const = 0;

    public:
      virtual void read(const jpath::object &p, const std::function<void (int)> &fn) const;
      virtual void read(const jpath::object &p, const std::function<void (const std::string &)> &fn) const;

    public:
      virtual void enumerate(const jpath::object &p, const std::function<void (int, const std::shared_ptr<jimage::accessor> &)> &fn) const;
  };

  class cref_accessor : public image::accessor
  {
    private:
      const Json::Value &_ref;

    public:
      cref_accessor(const Json::Value &ref);

    public:
      virtual ~cref_accessor() = default;

    private:
      virtual const Json::Value &value(void) const { return _ref; }
  };

} } }

#endif
