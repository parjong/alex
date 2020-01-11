#ifndef __PEPPER_BUILD_PROJECT_OP_BUILD_RUNNER_H__
#define __PEPPER_BUILD_PROJECT_OP_BUILD_RUNNER_H__

#include <core/op/runner.hpp>

#include <core/unit/op/build.hpp>
#include <core/project/desc.hpp>

namespace core { namespace project { namespace op { namespace build {

  class runner : public core::op::runner
  {
    private:
      const core::unit::op::build::runner &_ubuild;

    public:
      runner(const core::unit::op::build::runner &ubild);
      ~runner() = default;

    public:
      bool build(const project::desc &p);
  };

} } } }

#endif
