#ifndef __PEPPER_ENV_SYSTEM_OBJECT_H__
#define __PEPPER_ENV_SYSTEM_OBJECT_H__

#include <pepper/env/core.hpp>

namespace pepper { namespace env { namespace system {

  class object : core::object
  {
    public:
      object() = default;
      virtual ~object() = default;

    public:
      virtual pepper::maybe::object<std::string> get(const std::string &k);
      virtual core::setter::object set(const std::string &k);
  };

} } }

#endif
