#ifndef __PEPPER_ENV_SYSTEM_SETTER_SPEC_H__
#define __PEPPER_ENV_SYSTEM_SETTER_SPEC_H__

#include <pepper/env/core.hpp>

namespace pepper { namespace env { namespace system { namespace setter {

  class spec : public core::setter::spec
  {
    private:
      std::string _key;

    public:
      spec(const std::string &key);
      virtual ~spec() = default;

    public:
      virtual void set(const std::string &value);
  };

} } } }

#endif
