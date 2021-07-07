#include <pepper/env/reader.hpp>

#include <cstdlib>

namespace pepper { namespace env {

  reader::reader(const std::string &name) : _name{ name }
  {
    // DO NOTHING
  }

  bool reader::filled(void) const
  {
    return std::getenv(_name.c_str()) != nullptr;
  }

  bool reader::read(const probe &fn) const
  {
    auto p = std::getenv(_name.c_str());

    if (p == nullptr)
    {
      return false;
    }

    fn(p);
    return true;
  }

} }
