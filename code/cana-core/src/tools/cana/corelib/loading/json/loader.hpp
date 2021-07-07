#ifndef __CANA_CORELIB_LOADING_JSON_LOADER_H__
#define __CANA_CORELIB_LOADING_JSON_LOADER_H__

#include <cana/core/app/loader.hpp>

#include <cana/core/storage.hpp>
#include <cana/corelib/loading/json/package.hpp>

#include <istream>

namespace cana { namespace corelib { namespace loading { namespace json {

  class loader : public core::app::loader
  {
    private:
      std::istream &_is;
      const json::package &_package;
      const core::storage &_storage;

    public:
      loader(std::istream &, const json::package &, const core::storage &);
      virtual ~loader() = default;

    public:
      virtual void load(core::app::store &, const core::binder::catalog &);
  };

} } } }

#endif
