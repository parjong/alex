#ifndef __CAPTURE_LOWERING_RULE_H__
#define __CAPTURE_LOWERING_RULE_H__

#include "context.h"
#include "action.h"

#include <regex>

namespace lowering {

  class rule
  {
    private:
      std::regex _re;

    public:
      rule(const std::string &exp);

    private:
      std::vector<std::unique_ptr<action>> actions;

    public:
#define COMMAND(Name, ActionClass) rule &Name(void);
#include "command.lst"
#undef COMMAND

    public:
      bool apply(context &ctx) const;
  };

}

#endif
