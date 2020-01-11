#ifndef __PEPPER_BUILD_PROJECT_MANIFEST_H__
#define __PEPPER_BUILD_PROJECT_MANIFEST_H__

#include <pepper/json.hpp>

namespace core { namespace project { namespace manifest {

  namespace js = pepper::json::type;

  /** manifest */
  struct spec : public js::obj::value
  {
    js::map::field<js::seq::value<js::str::value>> deps;

    spec();
    virtual ~spec() = default;
  };

} } }

#endif
