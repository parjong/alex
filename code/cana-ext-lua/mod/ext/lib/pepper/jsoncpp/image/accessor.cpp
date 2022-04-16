#include <pepper/jsoncpp/image/accessor.hpp>
#include <pepper/jsoncpp/image/cref/accessor.hpp>
#include <pepper/jsoncpp/path.hpp>

#include <jsoncpp/json/json.h>

namespace pepper { namespace jsoncpp { namespace image {

  void accessor::read(const jpath::object &p, const std::function<void (int)> &fn) const
  {
    auto num = jsoncpp::path::make(p).access(value()).asInt();
    fn(num);
  }

  void accessor::read(const jpath::object &p, const std::function<void (const std::string &)> &fn) const
  {
    auto str = jsoncpp::path::make(p).access(value()).asString();
    fn(str);
  }

  void accessor::enumerate(const jpath::object &p, const std::function<void (int, const std::shared_ptr<jimage::accessor> &)> &fn) const
  {
    auto &node = jsoncpp::path::make(p).access(value());

    if (node.isArray())
    {
      for (int i = 0; i < node.size(); ++i)
      {
        auto acc = pepper::mem::shared::make<cref::accessor>(node[i]);
        fn(i, acc);
      }
    }
  }

} } }
