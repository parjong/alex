#ifndef __PEPPER_ENV_CORE_SETTER_SPEC_H__
#define __PEPPER_ENV_CORE_SETTER_SPEC_H__

#include <string>

namespace pepper { namespace env { namespace core { namespace setter {

  struct spec
  {
    spec() = default;
    virtual ~spec() = default;

    virtual void set(const std::string &) = 0;
  };

} } } }

#endif
