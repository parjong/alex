#ifndef __PEPPER_BUILD_UNIT_TYPE_CTXT_H_
#define __PEPPER_BUILD_UNIT_TYPE_CTXT_H_

#include <core/unit/type/base.hpp>

#include <map>
#include <memory>
#include <string>

namespace core { namespace unit { namespace type {

  struct ctxt : public std::map<std::string, std::unique_ptr<unit::type::base>>
  {
    ctxt() = default;
    virtual ~ctxt() = default;
  };

} } }

#endif
