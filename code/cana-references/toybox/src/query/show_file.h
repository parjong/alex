#ifndef SHOW_FILE_MODE_H__
#define SHOW_FILE_MODE_H__

#include "query/mode.h"

class ShowFileMode : public mode::action
{
  public:
    ShowFileMode();
    virtual ~ShowFileMode();
  public:
    virtual void run(Emit& emit, int argc, char **argv);
};

#endif
