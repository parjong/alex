#ifndef __CAPTURE_PARSING_ACTION_H__
#define __CAPTURE_PARSING_ACTION_H__

#include "context.h"

namespace parsing {

  struct action
  {
    virtual ~action() = default;

    virtual void run(parsing::context &ctx) const = 0;
  };

}

#endif
