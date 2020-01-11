#ifndef __PEPPER_APPFW_APP_SERVICE_CMDLINE_DESC_H__
#define __PEPPER_APPFW_APP_SERVICE_CMDLINE_DESC_H__

#include <pepper/optional.hpp>

#include <string>

namespace pepper { namespace appfw { namespace service { namespace cmdline {

  struct desc
  {
    desc() = default;
    virtual ~desc() = default;

    virtual optional::object<std::string> access(unsigned) const = 0;
  };

} } } }

#endif
