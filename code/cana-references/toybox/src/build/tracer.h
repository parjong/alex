#ifndef CONTROLLER_H__
#define CONTROLLER_H__

#include "context.h"


class Tracer
{
  public:
    Tracer();
    virtual ~Tracer();
  public:
    virtual void onEnterEvent(const EnterEventContext& ctxt) = 0;
    virtual void onLeaveEvent(const LeaveEventContext& ctxt) = 0;
    
    virtual void onExecEvent(const ExecEventContext& ctxt) = 0;
    virtual void onExitedEvent(const ExitedEventContext& ctxt) = 0;
};

#endif
