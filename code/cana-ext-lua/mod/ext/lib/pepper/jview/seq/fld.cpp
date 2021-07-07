#include <pepper/jview/seq/fld.hpp>
#include <pepper/jview/fld.hpp>

namespace pepper { namespace jview { namespace seq {

  fld::fld(const jview::obj &o, const std::string &name) : jview::fld{o, name}
  {
    // DO NOTHING
  }

  reader fld::read(const pepper::jimage::object &image) const
  {
    return reader{image, path()};
  }

} } }
