#ifndef __PEPPER_BUILD_NATIVE_FWK_BASE_H__
#define __PEPPER_BUILD_NATIVE_FWK_BASE_H__

#include <core/fwk/base.hpp>
#include <core/unit/type/ctxt.hpp>

namespace native { namespace fwk {

  class base : public core::fwk::base
  {
    private:
      const core::unit::type::ctxt &_types;

    public:
      virtual const core::unit::type::ctxt &types(void) const
      {
        return _types;
      }

    public:
      base(const core::unit::type::ctxt &types) : _types( types )
      {
        // DO NOTHING
      }

    public:
      virtual ~base() = default;
  };

} }

#endif
