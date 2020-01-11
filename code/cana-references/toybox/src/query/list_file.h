#ifndef LIST_FILE_MODE_H__
#define LIST_FILE_MODE_H__

#include "query/mode.h"

class ListFileMode : public mode::action
{
  public:
    ListFileMode();
    virtual ~ListFileMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};

#endif
