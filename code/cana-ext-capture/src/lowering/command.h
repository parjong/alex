#ifndef __CAPTURE_LOWERING_COMMAND_H__
#define __CAPTURE_LOWERING_COMMAND_H__

#include "rule.h"

namespace lowering {

  struct command
  {
    virtual ~command() = default;

    virtual void update(lowering::rule &r) const = 0;
  };

}

namespace lowering { namespace commands {

#define COMMAND(Name, ActionClass) \
  struct Name : public lowering::command \
  { \
    virtual ~Name() = default; \
    \
    virtual void update(lowering::rule &r) const \
    { \
      r.Name(); \
    } \
  };

#include "command.lst"
#undef COMMAND

} }

#endif
