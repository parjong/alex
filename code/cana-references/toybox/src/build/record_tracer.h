#ifndef RECORD_TRACER_H__
#define RECORD_TRACER_H__

#include "tracer.h"

#include "emit/emit.h"
#include "emit/command.h"

#include <map>

class RecordTracer : public Tracer
{
  public:
    RecordTracer(Emit& emit);
    virtual ~RecordTracer();
  private:
    Emit& emit_;
  private:
    std::map<pid_t, Command> running_;
  public:
    virtual void onEnterEvent(const EnterEventContext& ctxt);
    virtual void onLeaveEvent(const LeaveEventContext& ctxt);
    
    virtual void onExecEvent(const ExecEventContext& ctxt);
    virtual void onExitedEvent(const ExitedEventContext& ctxt);
};

#endif
