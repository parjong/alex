#include "rule.h"

namespace parsing {
namespace actions {

  struct stop : public parsing::action
  {
    stop(const std::string &arg)
    {
      // DO NOTHING
    }

    virtual ~stop() = default;

    virtual void run(parsing::context &ctx) const
    {
      ctx.stop();
    }
  };

  struct ignore : public parsing::action
  {
    ignore(const std::string &arg)
    {
      // DO NOTHING
    }

    virtual ~ignore() = default;

    virtual void run(parsing::context &ctx) const
    {
      ctx._args.pop_front();
    }
  };

  struct tag : public parsing::action
  {
    std::string _tag;

    tag(const std::string &tag) : _tag(tag)
    {
      // DO NOTING
    }

    virtual ~tag() = default;

    virtual void run(parsing::context &ctx) const
    {
      ctx.tagged(ctx._args.front(), _tag);
    }
  };

} }

namespace parsing {

  rule::rule(const std::string &s) : _re(s)
  {
    // DO NOTHING
  }

  bool rule::check(const std::string &arg) const
  {
    return std::regex_match(arg, _re);
  }

#define COMMAND(Name, Action) \
  rule &rule::Name(const std::string &arg) \
  { \
    actions.emplace_back(new actions::Action(arg)); \
    return (*this); \
  }

#include "command.lst"
#undef COMMAND

  void rule::apply(parsing::context &ctx) const
  {
    for (const auto &action : actions)
    {
      action->run(ctx);
    }
  }

}
