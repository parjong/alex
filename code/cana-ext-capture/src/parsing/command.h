#ifndef __CAPTURE_PARSING_COMMAND_H__
#define __CAPTURE_PARSING_COMMAND_H__

#include "rule.h"

namespace parsing {

  struct command
  {
    virtual ~command() = default;

    virtual void update(parsing::rule &r, const std::string &arg) const = 0;
  };

}

namespace parsing {
namespace commands {

#define COMMAND(Name, ActionClass) \
  struct Name : public parsing::command \
  { \
    virtual ~Name() = default; \
    \
    virtual void update(parsing::rule &r, const std::string &arg) const \
    { \
      r.Name(arg); \
    } \
  };

#include "command.lst"
#undef COMMAND

}
}
#endif
