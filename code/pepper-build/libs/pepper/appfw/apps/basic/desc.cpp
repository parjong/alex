#include <pepper/appfw/apps/basic/desc.hpp>

namespace pepper { namespace appfw { namespace apps { namespace basic {

  void desc::enroll(app::option::set &)
  {
    // DO NOTHING
  }

  void desc::enroll(app::command::set &)
  {
    // DO NOTHING
  }

  void desc::invoke(appfw::service::desc &srv)
  {
    basic::service bs{ srv };

    srv.exitcode().set( main(bs) );    
  }

} } } }
