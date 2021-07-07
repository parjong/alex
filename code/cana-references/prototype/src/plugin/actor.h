#ifndef BC_ACTOR_H__
#define BC_ACTOR_H__

#include <string>

#include "base/arg-data.h"
#include "base/env-data.h"
#include "plugin/abstract_system.h"

class actor
{
  public:
    actor();
  public:
    virtual ~actor();
  public:
    virtual void perform(const abstract_system& sys,
                         const std::string& wd, 
                         const std::string& path, 
                         const arg_data& arg,
                         const env_data& env) const = 0;
};

#endif
