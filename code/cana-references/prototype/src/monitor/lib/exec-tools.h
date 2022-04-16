#ifndef BC_EXEC_TOOLS_H__
#define BC_EXEC_TOOLS_H__

#include <string>

#include "base/arg-data.h"
#include "base/env-data.h"

int run_in_current(const std::string& path, const arg_data& arg, const env_data& env);

typedef enum
{
  CHILD_FAILED,
  CHILD_EXITED,
  CHILD_SIGNALED,
} child_status_t;

child_status_t run_at_child(const std::string& path, const arg_data& arg, const env_data& env, int *retcode);

#endif
