#ifndef __PEPPER_BUILD_UNIT_CTXT_H__
#define __PEPPER_BUILD_UNIT_CTXT_H__

#include <core/unit/desc.hpp>

namespace core { namespace unit {

  struct ctxt : public std::vector<std::unique_ptr<unit::desc>>  
  {
    ctxt() = default;
    ~ctxt() = default;
  };

} }

#endif
