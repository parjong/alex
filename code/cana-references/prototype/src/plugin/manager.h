#ifndef BC_PLUGIN_MANAGER_H__
#define BC_PLUGIN_MANAGER_H__

#include "plugin/checker.h"
#include "plugin/actor.h"

#include <vector>

class manager
{
  private:
    class plugin
    {
      public:
        plugin(const checker& chk, const actor& act);
      private:
        const checker& chk_;
        const actor& act_;
      public:
        const checker& get_checker(void) const;
        const actor& get_actor(void) const;
    };
  public:
    manager();
  public:
    ~manager(); 
  private:
    std::vector<plugin *> plugins_;
  public:
    void enroll(const checker& chk, const actor& act);
    const actor *lookup(const std::string& path);
  public:
    static manager& instance(void);
};

#endif 
