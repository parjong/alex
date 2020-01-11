#include "engine.h"

namespace lowering {

  lowering::rule &engine::rule(const std::string &s)
  {
    lowering::rule *ptr = new lowering::rule(s);
    std::unique_ptr<lowering::rule> uni(ptr);
    rules.emplace_back(std::move(uni));
    return (*ptr);
  }

  void engine::run(context &ctx) const
  {
    for (const auto &rule : rules)
    {
      if (rule->apply(ctx))
      {
        break;
      }
    }
  }
}
