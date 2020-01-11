#ifndef __PEPPER_BUILD_UNIT_OP_BUILD_RUNNER_H__
#define __PEPPER_BUILD_UNIT_OP_BUILD_RUNNER_H__

#include <core/op/runner.hpp>

#include <core/fwk/manager.hpp>
#include <core/unit/desc.hpp>

namespace core { namespace unit { namespace op { namespace build {

  class runner : public core::op::runner
  {
    private:
      const core::fwk::manager &_frameworks;

    public:
      bool build(const core::unit::desc &u) const;

    public:
      runner(const core::fwk::manager &frameworks);
      ~runner() = default;
  };

} } } }

#endif
