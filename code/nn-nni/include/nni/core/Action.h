#ifndef __NNI_CORE_ACTION_H__
#define __NNI_CORE_ACTION_H__

#include "State.h"

struct Action
{
  virtual ~Action() = default;

  virtual void run(State &) = 0;
};

#endif // __NNI_CORE_ACTION_H__
