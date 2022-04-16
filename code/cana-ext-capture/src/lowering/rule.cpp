#include "rule.h"

namespace lowering { namespace actions {

  class forward : public lowering::action
  {
    virtual ~forward() = default;

    virtual void run(std::stack<std::string> &stk, context &ctx) const
    {
      ctx.forward(stk.top());
      stk.pop();
    }
  };

  class skip : public lowering::action
  {
    virtual ~skip() = default;

    virtual void run(std::stack<std::string> &stk, context &ctx) const
    {
      stk.pop();
    }
  };

} }

namespace lowering {

  rule::rule(const std::string &exp) : _re(exp)
  {
    // DO NOTHING
  }

#define COMMAND(Name, ActionClass) \
  rule &rule::Name() \
  { \
    actions.emplace_back(new actions::ActionClass()); \
    return (*this); \
  }
#include "command.lst"
#undef COMMAND

  bool rule::apply(context &ctx) const
  {
    std::smatch match;

    if (!std::regex_match(ctx.front(), match, _re))
    {
      return false;
    }

    std::stack<std::string> stk;

    for (size_t ind = match.size() - 1; ind > 0; --ind)
    {
      stk.push(match.str(ind));
    }

    for (const auto &action : actions)
    {
      action->run(stk, ctx);
    }

    // TODO Throw an exception if stk is not empty
    return true;
  }

}
