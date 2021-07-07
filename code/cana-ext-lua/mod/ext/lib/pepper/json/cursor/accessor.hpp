#ifndef __PEPPER_JSON_CURSOR_ACCESSOR_H__
#define __PEPPER_JSON_CURSOR_ACCESSOR_H__

#include <jsoncpp/json/value.h>

namespace pepper { namespace json { namespace cursor {

  struct accessor
  {
    accessor() = default;
    virtual ~accessor() = default;

    virtual Json::Value &get_writer(void) const = 0;
    virtual const Json::Value &get_reader(void) const = 0;
  };

} } }

#endif
