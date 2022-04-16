#ifndef __CAPTURE_LOWERING_ACTION_H__
#define __CAPTURE_LOWERING_ACTION_H__

#include "context.h"

#include <stack>
#include <string>

namespace lowering {

  struct action
  {
    virtual ~action() = default;

    virtual void run(std::stack<std::string> &stk, context &ctx) const = 0;
  };

}

#endif
