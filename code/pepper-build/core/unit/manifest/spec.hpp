#ifndef __PEPPER_BUILD_UNIT_MANIFEST_SPEC_H__
#define __PEPPER_BUILD_UNIT_MANIFEST_SPEC_H__

#include <pepper/json.hpp>

namespace core { namespace unit { namespace manifest {

  namespace js = pepper::json::type;

  struct spec : public js::obj::value
  {
    js::str::field framework;
    js::str::field type;
    
    spec();
    virtual ~spec() = default;
  };

} } }

#endif
