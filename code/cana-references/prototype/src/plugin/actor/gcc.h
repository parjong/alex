#ifndef BC_GCC_PLUGIN_H__
#define BC_GCC_PLUGIN_H__

#include "plugin/actor.h"

class gcc_actor : public actor
{
  public:
    gcc_actor();
  public:
    virtual ~gcc_actor();
  public:
    virtual void perform(const abstract_system& sys,
                         const std::string& wd, 
                         const std::string& path, 
                         const arg_data& arg,
                         const env_data& env) const;
};


#endif
