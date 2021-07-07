#ifndef __NNI_CORE_SESSION_H__
#define __NNI_CORE_SESSION_H__

#include "State.h"

#include <functional>

struct Session
{
  virtual ~Session() = default;

  virtual bool prepare(const std::function<void (State &)> &cb) = 0;
  virtual bool invoke(void) = 0;
  virtual bool teardown(const std::function<void (State &)> &cb) = 0;
};

#endif // __NNI_CORE_SESSION_H__
