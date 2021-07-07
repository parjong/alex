#include <pepper/appfw/apps/nested/command.hpp>
#include <pepper/appfw/app/desc.hpp>

namespace pepper { namespace appfw { namespace apps { namespace nested {

  command& command::set(const std::shared_ptr<app::desc> &app)
  {
    _app = app;
    return *this;
  }

  void command::enroll(app::command::set &s, const std::string &name)
  {
    if ( _app != nullptr )
    {
      s.enroll( name, _app );
    }
  }

} } } }
