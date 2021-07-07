#ifndef __CAPTURE_LOWERING_ENGINE_H__
#define __CAPTURE_LOWERING_ENGINE_H__

#include "rule.h"

#include <memory>
#include <vector>

namespace lowering {

  class engine
  {
    private:
      std::vector<std::unique_ptr<lowering::rule>> rules;

    public:
      lowering::rule &rule(const std::string &s);

    public:
      void run(context &ctx) const;
  };

}

#endif
