#ifndef BC_HOOK_MANAGER_H__
#define BC_HOOK_MANAGER_H__

#include "base/env-data.h"
#include "base/distrib-data.h"

#include <string>

namespace hook
{
  class plugin
  {
    public:
      plugin() { }
      virtual ~plugin() { }
    public:
      virtual void enable(env_data& env) const = 0;
      virtual void disable(env_data& env) const = 0;
  };

  class libc_plugin : public plugin
  {
    public:
      libc_plugin(const distrib_data& dist) : dist_(dist) { }
    private:
      const distrib_data& dist_;
    public:
      virtual void enable(env_data& env) const
      {
        std::string libpath = dist_.libdir() + "/lib.so";
        env.insert("LD_PRELOAD", libpath);
      }
    public:
      virtual void disable(env_data& env) const
      {
        env.erase("LD_PRELOAD");
      }
  };
}

#endif
