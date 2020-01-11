#include "engine.h"

namespace parsing {

  parsing::rule &engine::rule(const std::string &s)
  {
    auto ptr = new parsing::rule(s);
    rules.emplace_back(ptr);
    return (*ptr);
  }

  bool engine::run(parsing::context &ctx) const
  {
    for (const auto &rule : rules)
    {
      if (!rule->check(ctx._args.front()))
      {
        continue;
      }

      rule->apply(ctx);
      return true;
    }
    return false;
  }

}
