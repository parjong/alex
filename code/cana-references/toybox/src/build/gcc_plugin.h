#ifndef GCC_PLUGIN_H__
#define GCC_PLUGIN_H__

#include "build/plugin.h"

#include "emit/emit.h"

class GCCPlugin : public Plugin
{
  public:
    GCCPlugin(Emit& emit);
    virtual ~GCCPlugin();
  private:
    Emit& emit_;
  public:
    void run(hiberlite::sqlid_t id, const Command& cmd);
};


#endif
