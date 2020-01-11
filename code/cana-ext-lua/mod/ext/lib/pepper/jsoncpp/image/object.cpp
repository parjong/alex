#include <pepper/jsoncpp/image/object.hpp>
#include <pepper/jsoncpp/image/value/accessor.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace jsoncpp { namespace image {

  jimage::object make(std::istream &is)
  {
    return pepper::mem::shared::make<jimage::accessor, jsoncpp::image::value::accessor>(is);
  }

} } }
