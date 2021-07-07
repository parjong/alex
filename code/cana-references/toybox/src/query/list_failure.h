#ifndef LIST_FAILURE_H__
#define LIST_FAILURE_H__

#include "query/mode.h"

class ListFailureMode : public mode::action
{
  public:
    ListFailureMode();
    virtual ~ListFailureMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};

#endif
