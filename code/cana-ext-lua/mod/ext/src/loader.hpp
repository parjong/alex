#ifndef __CANA_BINDER_LUA_LOADER_H__
#define __CANA_BINDER_LUA_LOADER_H__

#include <cana/ext/loader.hpp>

namespace cana { namespace binder { namespace lua {

  class loader : public cana::ext::loader
  {
    public:
      loader() = default;
      virtual ~loader() = default;

    public:
      virtual std::unique_ptr<cana::ext::app> load(const cana::ext::service &) const;
  };

} } }

#endif
