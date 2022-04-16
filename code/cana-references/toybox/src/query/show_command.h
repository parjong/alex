#ifndef SHOW_COMMAND_MODE_H__
#define SHOW_COMMAND_MODE_H__

#include "query/mode.h"

class ShowCommandMode : public mode::action
{
  public:
    ShowCommandMode();
    virtual ~ShowCommandMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};

#endif
