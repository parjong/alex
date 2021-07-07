#ifndef LIST_COMMAND_H__
#define LIST_COMMAND_H__

#include "query/mode.h"

class ListCommandMode : public mode::action
{
  public:
    ListCommandMode();
    virtual ~ListCommandMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};


#endif
