#include "monitor/lib/linux-system.h"

#include "monitor/lib/exec-tools.h"

linux_system::linux_system() { }
linux_system::~linux_system() { }

abstract_system::status linux_system::run(const std::string& path, const arg_data& arg, const env_data& env) const
{
  switch ( run_at_child(path, arg, env, nullptr) )
  {
    case CHILD_FAILED: 
      return FAILED;
    case CHILD_EXITED:
      return EXITED;
    case CHILD_SIGNALED:
      return SIGNALED;
    default:
      break;
  }

  return FAILED;
}

