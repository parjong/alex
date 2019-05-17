#ifndef __HERMES_SINK_H__
#define __HERMES_SINK_H__

#include "hermes/Log.h"

#include <memory>

namespace hermes
{

struct Sink
{
  virtual ~Sink() = default;

  virtual void notify(const Log *) = 0;
};

struct SinkRegistry
{
  virtual ~SinkRegistry() = default;

  // NOTE SinkRegistry takes the ownership of all the appended Sink objects
  virtual void append(std::unique_ptr<Sink> &&) = 0;
};

} // namespace hermes

#endif // __HERMES_SINK_H__
