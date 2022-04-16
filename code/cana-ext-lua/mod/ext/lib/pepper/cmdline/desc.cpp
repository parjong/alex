#include <pepper/cmdline/desc.hpp>

#include <pepper/mem.hpp>

namespace pepper { namespace cmdline { namespace simple {

  option::desc &desc::option(const std::string &tag)
  {
    auto o = mem::shared::make<option::desc>( );

    _table.insert( tag, o );

    return *o;
  }

  optional::object<action::bean> desc::lookup(const std::string &tag) const
  {
    auto bean_fn = [] (const std::shared_ptr<option::desc> &d)
    {
      return pepper::cmdline::action::bean{ d->action() };
    };

    return _table.lookup(tag).map<action::bean>(bean_fn);
  }

} } }
