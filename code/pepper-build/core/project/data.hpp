#ifndef __PEPPER_BUILD_PROJECT_DATA_H__
#define __PEPPER_BUILD_PROJECT_DATA_H__

#define FORWARD_DECL
#include <core/project/desc.hpp>
#undef  FORWARD_DECL

#include <core/unit/desc.hpp>
#include <core/unit/ctxt.hpp>

#include <core/project/pathname/root.hpp>
#include <core/project/manifest/spec.hpp>

#include <pepper/attr.hpp>

namespace core { namespace project {

  class data
  {
    private:
      const core::project::desc &_base;
    public:
      const core::project::desc &base(void) const;

    public:
      data(const core::project::desc &base);
      ~data() = default;

    public:
      pepper::attr::lazy::reader<project::manifest::spec> manifest;
      pepper::attr::lazy::reader<core::unit::ctxt> units;
  };

} }

#endif
