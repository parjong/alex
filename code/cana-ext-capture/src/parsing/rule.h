#ifndef __CAPTURE_PARSING_RULE_H__
#define __CAPTURE_PARSING_RULE_H__

#include "context.h"
#include "action.h"

#include <memory>
#include <vector>
#include <regex>

namespace parsing {

  class rule
  {
    private:
      std::regex _re;

    public:
      rule(const std::string &s);

    public:
      bool check(const std::string &arg) const;

    private:
      std::vector<std::unique_ptr<action>> actions;

    public:
#define COMMAND(Name, Action) rule &Name(const std::string &arg);
#include "command.lst"
#undef COMMAND

    public:
      void apply(parsing::context &ctx) const;
  };

}

#endif
