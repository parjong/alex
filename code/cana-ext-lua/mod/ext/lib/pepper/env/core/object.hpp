#ifndef __PEPPER_ENV_CORE_OBJECT_H__
#define __PEPPER_ENV_CORE_OBJECT_H__

#include <pepper/env/core/setter.hpp>
#include <pepper/maybe.hpp>

#include <string>

namespace pepper { namespace env { namespace core {

  struct object
  {
    object() = default;
    virtual ~object() = default;

    virtual core::setter::object set(const std::string &name) = 0;
    virtual pepper::maybe::object<std::string> get(const std::string &name) = 0;
  };

} } }

#endif
