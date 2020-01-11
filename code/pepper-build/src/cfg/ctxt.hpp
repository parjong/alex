#ifndef __PEPPER_BUILD_CFG_CTXT_H__
#define __PEPPER_BUILD_CFG_CTXT_H__

#include <core/unit/type/ctxt.hpp>
#include <core/fwk/manager.hpp>
#include <native/toolchain/build/ctxt.hpp>

#include <boost/filesystem.hpp>

namespace cfg {

  class ctxt 
  {
    private:
      native::toolchain::build::ctxt _toolchains;

    private:
      core::unit::type::ctxt _types;

    private:
      core::fwk::manager _frameworks;
    public:
      const core::fwk::manager &frameworks(void) const;

    public:
      ctxt(const boost::filesystem::path &root);
      ~ctxt() = default;
  };

}

#endif
