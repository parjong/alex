#ifndef __XRAY_H__
#define __XRAY_H__

#ifdef XRAY_TRACER
#define XRAY_ATTR __attribute__(())
#else
#define XRAY_ATTR __attribute__((weak))
#endif

#include <string>
#include <memory>

namespace xray
{

using EventIndex = uint64_t;

struct EventDomain
{
  // Non-virtual

  // This interface is useful for tooling. For example, it allows us to build as a generic tracer.
  virtual std::unique_ptr<std::string> what(const EventIndex &) const
  {
    // Default implementation
    return nullptr;
  }
};

struct EventHnd
{
  const EventDomain *domain;
  EventIndex index;
};

// Event
//   id & cat
// EventCategory
//   id to event details

struct endpoint
{
  static XRAY_ATTR void post(const EventHnd *);
};

} // namespace xray

#endif // __XRAY_H__
