#include <pepper/env/system/object.hpp>
#include <pepper/env/system/setter/spec.hpp>
#include <pepper/mem.hpp>

#include <cstdlib>

namespace pepper { namespace env { namespace system {

  pepper::maybe::object<std::string> object::get(const std::string &key)
  {
    auto value = std::getenv(key.c_str());
    
    if (value == nullptr)
    {
      return pepper::maybe::none<std::string>();
    }

    return pepper::maybe::some<std::string>(value);
  }

  core::setter::object object::set(const std::string &key)
  {
    return pepper::mem::shared::make<core::setter::spec, system::setter::spec>(key);
  }

} } }
