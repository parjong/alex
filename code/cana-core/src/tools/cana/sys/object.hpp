#ifndef __CANA_CORE_OBJECT_H__
#define __CANA_CORE_OBJECT_H__

#include <cana/core/binder/catalog.hpp>
#include <cana/core/binder/loader.hpp>

#include <cana/core/app/store.hpp>
#include <cana/core/app/loader.hpp>

namespace cana { namespace sys {

  class object
  {
    private:
      core::binder::catalog _catalog;
      core::app::store   _store;

    public:
      object();
   
    public:
      void load(core::binder::loader &loader);
      void load(core::app::loader &loader);

    public:
      void notifyProcessEnter(const cana::proc::info &pi);
      void notifyProcessLeave(const cana::proc::info &pi);
  };

} }

#endif
