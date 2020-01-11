#ifndef __PEPPER_BUILD_CORE_FWK_BASE_H__
#define __PEPPER_BUILD_CORE_FWK_BASE_H__

#include <core/unit/type/ctxt.hpp>

namespace core { namespace fwk { 

  struct base 
  {
    base() = default;
    virtual ~base() = default;

    virtual const core::unit::type::ctxt &types(void) const = 0;
  };

} }

#endif
