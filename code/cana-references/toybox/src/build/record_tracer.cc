#include "record_tracer.h"

#include "gcc_plugin.h"

#include <assert.h>
#include <iostream>

RecordTracer::RecordTracer(Emit& emit)
  : emit_(emit)
{ 
  // Do NOTHING 
}

RecordTracer::~RecordTracer() 
{ 
  // Do NOTHING 
}

void RecordTracer::onEnterEvent(const EnterEventContext& ctxt) 
{
  if ( ctxt.regs().orig_rax != 59 ) return;

  const char *path = (const char *) ctxt.regs().rdi;
  const char **arg = (const char **) ctxt.regs().rsi;
  const char **env = (const char **) ctxt.regs().rdx;

  auto it = running_.find(ctxt.pid());

  if ( it == running_.end() )
  {
    running_.emplace(ctxt.pid(), Command(ctxt, path, arg, env));
  }
  else
  {
    it->second.update(ctxt, path, arg, env);
  }
}

void RecordTracer::onLeaveEvent(const LeaveEventContext& ctxt) 
{ 
  // Do NOTHING 
}

void RecordTracer::onExecEvent(const ExecEventContext& ctxt) 
{
  auto it = running_.find(ctxt.pid());

  assert( it != running_.end() );

  it->second.setStart();
}

void RecordTracer::onExitedEvent(const ExitedEventContext& ctxt) 
{
  auto it = running_.find(ctxt.pid());

  if ( it == running_.end() ) 
  {
    // No information exists for the exited process 
    return;
  }

  it->second.setFinish();

  hiberlite::bean_ptr<Command> bean = emit_.commit(it->second);
 
  // Run plugin if necesary   
  GCCPlugin plugin(emit_);

  plugin.run(bean.get_id(), it->second);

  // Erase from the running process
  running_.erase(ctxt.pid()); 
}
