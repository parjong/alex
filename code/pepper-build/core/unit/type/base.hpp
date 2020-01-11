#ifndef __PEPPER_BUILD_UNIT_TYPE_BASE_H__
#define __PEPPER_BUILD_UNIT_TYPE_BASE_H__

#include "core/unit/desc.hpp"

namespace core { namespace unit { namespace type {

  struct base
  {
    base() = default;
    virtual ~base() = default;

    virtual void build(const unit::desc &p) = 0;
  };

} } }

#endif
