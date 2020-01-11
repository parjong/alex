#ifndef EXECUTE_MODE_H__
#define EXECUTE_MODE_H__

#include "query/mode.h"

class ExecuteMode : public mode::action
{
  public:
    ExecuteMode();
    virtual ~ExecuteMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};

#endif
