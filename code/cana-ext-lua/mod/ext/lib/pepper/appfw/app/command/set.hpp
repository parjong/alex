#ifndef __PEPPER_APPFW_APP_COMMAND_SET_H__
#define __PEPPER_APPFW_APP_COMMAND_SET_H__

#include <pepper/appfw/app/desc.forward.hpp>
#include <pepper/mem.hpp>

#include <string>

namespace pepper { namespace appfw { namespace app { namespace command {

  struct set 
  {
    set() = default;
    virtual ~set() = default;

    virtual void enroll( const std::string &name, const std::shared_ptr<app::desc> &app ) = 0;
  };

} } } }

#endif
