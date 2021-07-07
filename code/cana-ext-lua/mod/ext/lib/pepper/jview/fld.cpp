#include <pepper/jview/fld.hpp>

namespace pepper { namespace jview {

  fld::fld(const jview::obj &o, const std::string &name) : _path{o.path().named(name)}
  {
    // DO NOTHING
  }

  const pepper::jpath::object &fld::path(void) const
  {
    return _path;
  }

} }
