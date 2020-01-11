#ifndef __PEPPER_APPFW_APP_OPTION_DESC_H__
#define __PEPPER_APPFW_APP_OPTION_DESC_H__

#include <string>

namespace pepper { namespace appfw { namespace app { namespace option {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual void notify(const std::string &) = 0;
  };

} } } }

#endif // __PEPPER_APPFW_APP_OPTION_DESC_H__
