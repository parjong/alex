#include <cana/sys/object.hpp>

namespace cana { namespace sys {

  object::object()
  {
    // DO NOTHING
  }

  void object::load(core::binder::loader &loader)
  {
    loader.load(_catalog);
  }

  void object::load(core::app::loader &loader)
  {
    loader.load(_store, _catalog);
  }

  void object::notifyProcessEnter(const cana::proc::info &pi)
  {
    auto fn = [&] (core::app::tracker &plugin)
    {
      plugin.notifyProcessEnter(pi);
    };

    _store.each(fn);
  }

  void object::notifyProcessLeave(const cana::proc::info &pi)
  {
    auto fn = [&] (core::app::tracker &plugin)
    {
      plugin.notifyProcessLeave(pi);
    };

    _store.each(fn);
  }

} }
