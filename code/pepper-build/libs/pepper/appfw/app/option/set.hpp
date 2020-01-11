#ifndef __PEPPER_APPFW_APP_OPTION_SET_H__
#define __PEPPER_APPFW_APP_OPTION_SET_H__

#include <pepper/appfw/app/option/desc.hpp>

namespace pepper { namespace appfw { namespace app { namespace option {

  struct set
  {
    set( ) = default;
    virtual ~set( ) = default;

    virtual void enroll( const std::string &name, option::desc &desc ) = 0;
  };

} } } }

#endif // __PEPPER_APPFW_APP_OPTION_SET_H__
