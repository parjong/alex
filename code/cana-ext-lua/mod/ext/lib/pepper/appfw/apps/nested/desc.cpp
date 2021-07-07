#include <pepper/appfw/apps/nested/desc.hpp>
#include <pepper/appfw/apps/nested/command.hpp>

#include <pepper/mem.hpp>

namespace pepper { namespace appfw { namespace apps { namespace nested {

  nested::command &desc::command(const std::string &name)
  {
    auto it = _commands.find( name );

    if ( it == _commands.end() )
    {
      return _commands[ name ] = nested::command{ }; 
    }

    return (*it).second;
  }

  void desc::enroll(app::option::set &)
  {
    // DO NOTHING
  }

  void desc::enroll(app::command::set &s)
  {
    for (auto it = _commands.begin(); it != _commands.end(); ++it)
    {
      (*it).second.enroll(s, it->first);
    }
  }

  void desc::invoke(appfw::service::desc &srv)
  {
    // DO NOTHING
  }

} } } }
