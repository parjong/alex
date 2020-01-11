#ifndef BC_LINUX_SYSTEM_H__
#define BC_LINUX_SYSTEM_H__

#include "plugin/abstract_system.h"

class linux_system : public abstract_system
{
  public:
    linux_system();
    virtual ~linux_system();
  public:
    virtual status run(const std::string& path, const arg_data& arg, const env_data& env) const;
};

#endif
