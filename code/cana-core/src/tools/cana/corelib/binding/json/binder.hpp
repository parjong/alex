#ifndef __CANA_CORELIB_BINDING_JSON_BINDER_H__
#define __CANA_CORELIB_BINDING_JSON_BINDER_H__

#include <cana/corelib/binding/json/package.hpp>
#include <cana/core/binder/loader.hpp>

#include <istream>

namespace cana { namespace corelib { namespace binding { namespace json {

  class loader : public core::binder::loader
  {
    private:
      std::istream &_is;
      const json::package &_package;

    public:
      loader(std::istream &, const json::package &);
      virtual ~loader() = default;

    public:
      virtual void load(core::binder::catalog &);
  };

} } } }

#endif
