#ifndef __CAPTURE_PARSING_ENGINE_H__
#define __CAPTURE_PARSING_ENGINE_H__

#include "context.h"
#include "rule.h"

#include <memory>
#include <vector>

namespace parsing {

  class engine
  {
    private:
      std::vector<std::unique_ptr<parsing::rule>> rules;

    public:
      parsing::rule &rule(const std::string &pat);

    public:
      bool run(parsing::context &ctx) const;
  };
}

#endif
