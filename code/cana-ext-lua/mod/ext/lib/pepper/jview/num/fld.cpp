#include <pepper/jview/num/fld.hpp>

namespace pepper { namespace jview { namespace num {

  fld::fld(const jview::obj &o, const std::string &name) : jview::fld{o, name}
  {
    // DO NOTHING
  }

  reader fld::read(const jimage::object &image) const
  {
    return reader{image, path()};
  }

} } }
