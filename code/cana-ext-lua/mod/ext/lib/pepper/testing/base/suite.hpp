#ifndef __PEPPER_TESTING_BASE_SUITE_H__
#define __PEPPER_TESTING_BASE_SUITE_H__

#include <pepper/testing/base/unit.hpp>

#include <functional>
#include <string>

namespace pepper { namespace testing { namespace base {

  struct suite
  {
    suite() = default;
    virtual ~suite() = default;

    virtual const std::string name(void) const = 0;
    virtual void foreach(const std::function<void (const unit *)> &fn) const = 0;
  };

} } }

#endif
