#ifndef __PEPPER_TESTING_BASE_UNIT_H__
#define __PEPPER_TESTING_BASE_UNIT_H__

#include <string>

namespace pepper { namespace testing { namespace base {

  struct unit
  {
    unit() = default;
    virtual ~unit() = default;

    virtual const std::string name(void) const = 0;
    virtual void run(void) const = 0;
  };

} } }

#endif
