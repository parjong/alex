#ifndef BC_PLUGIN_ABSTRACT_SYSTEM_H__
#define BC_PLUGIN_ABSTRACT_SYSTEM_H__

#include <string>

#include "base/arg-data.h"
#include "base/env-data.h"

class abstract_system
{
  public:
    abstract_system();
    virtual ~abstract_system();
  public:
    typedef enum
    {
      FAILED,
      EXITED,
      SIGNALED,
    } status;
  public:
    virtual status run(const std::string& path, const arg_data& arg, const env_data& env) const = 0;
};

#endif
