#include <pepper/appfw/cli/command/set.hpp>

namespace pepper { namespace appfw { namespace cli { namespace command {

  void set::enroll( const std::string &name, const std::shared_ptr<pepper::appfw::app::desc> &app )
  {
    _dict().insert( name, app );
  }

  set::set(dict &d) : _dict{ d }
  {
    // DO NOTHING
  }

} } } }
