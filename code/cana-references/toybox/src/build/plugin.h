#ifndef PLUGIN_H__
#define PLUGIN_H__

#include "emit/command.h"

class Plugin
{
  public:
    Plugin();
    virtual ~Plugin();
  public:
    virtual void run(hiberlite::sqlid_t id, const Command& cmd) = 0;
};

#endif
