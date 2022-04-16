#ifndef __CANA_BINDER_NATIVE_LOADER_H__
#define __CANA_BINDER_NATIVE_LOADER_H__

#include <cana/ext/loader.hpp>

namespace cana { namespace binder { namespace native {

  class loader : public cana::ext::loader
  {
    public:
      loader() = default;
      virtual ~loader() = default;

    public:
      virtual std::unique_ptr<ext::app> load(const ext::service &) const;
  };

} } }

#endif
