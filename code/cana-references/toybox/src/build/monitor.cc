#include "monitor.h"

#include <assert.h>

#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

/**
 *
 */
SyscallStatus::SyscallStatus()  { }
SyscallStatus::~SyscallStatus() { }

void SyscallStatus::clear(pid_t pid) 
{
  entered_.erase(pid);
}

void SyscallStatus::update(pid_t pid)
{
  auto it = entered_.find(pid);

  if ( it == entered_.end() )
    entered_.insert(pid);
  else
    entered_.erase(pid);
}

bool SyscallStatus::check(pid_t pid) const
{
  return entered_.count(pid) > 0;
}

/**
 *
 */
Monitor::Monitor(Tracee& tracee, Tracer& tracer) 
  : tracee_(tracee), tracer_(tracer) 
{ }

Monitor::~Monitor() { }

void Monitor::do_child(void)
{
  /** Step 1. Setup */
  ptrace(PTRACE_TRACEME, 0, NULL, NULL);
  raise(SIGSTOP);

  /** Step 2. Run */
  tracee_.run();

  /** Step 3. Teardown */
  exit(127);  
}

Terminator *Monitor::do_parent(pid_t tracee)
{
  /** Wait for PTRACE_TRACEME */
  assert( waitpid(tracee, NULL, 0) != -1 );

  /** Set trace options */
  long options = 0;

  options |= PTRACE_O_TRACEEXIT;
  options |= PTRACE_O_TRACEEXEC;
  options |= PTRACE_O_TRACEFORK;
  options |= PTRACE_O_TRACECLONE;
  options |= PTRACE_O_TRACEVFORK;
  options |= PTRACE_O_TRACEVFORKDONE;
  options |= PTRACE_O_TRACESYSGOOD;

  ptrace(PTRACE_SETOPTIONS, tracee, NULL, options);

  /** Resume */
  ptrace(PTRACE_SYSCALL, tracee, 0, 0);

  /** Iterate */
  while ( 1 )
  {
    int status = 0;

    pid_t child = waitpid(-1, &status, __WALL);

    if ( child == -1 ) break;

    if ( WIFEXITED(status) )
    {
      /** Step 1. */
      int code = WEXITSTATUS(status);

      /** Step 2. */
      status_.clear(child);

      /** Step 3. */
      if ( child == tracee ) 
        return new ExitedTerminator(code);

      continue;
    }

    if ( WIFSIGNALED(status) )
    {
      /** Step 1. */
      int sig = WTERMSIG(status);

      /** Step 2. */
      status_.clear(child);

      /** Step 3. */
      if ( child == tracee )
        return new SignaledTerminator(sig);

      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_EXIT << 8)) )
    {
      ExitedEventContext ctxt(child);

      tracer_.onExitedEvent(ctxt);

      ptrace(PTRACE_SYSCALL, child, 0, 0);

      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_EXEC << 8)) )
    {
      ExecEventContext  ctxt(child);

      tracer_.onExecEvent(ctxt);

      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_FORK<<8)) )
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)) )
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)) )
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( (status >> 8) == (SIGTRAP | (PTRACE_EVENT_VFORK_DONE<<8)) )
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( (status >> 8) == (SIGTRAP | 0x80) )
    {
      if ( status_.check(child ) )
      {
        LeaveEventContext ctxt(child);

        tracer_.onLeaveEvent(ctxt);       
      }
      else
      {
        EnterEventContext ctxt(child);

        tracer_.onEnterEvent(ctxt);       
      }

      status_.update(child);

      ptrace(PTRACE_SYSCALL, child, 0, 0);
      continue;
    }

    if ( WIFSTOPPED(status) )
    {
      int sig = WSTOPSIG(status);

      ptrace(PTRACE_SYSCALL, child, 0, sig);
      continue;
    }

    assert(0 && "CONTINUED should not be captured");
  }

  return new SignaledTerminator(SIGKILL);
}

Terminator *Monitor::trace(void)
{
  pid_t pid = fork();

  assert( pid != -1 );

  if ( pid == 0 )
  {
    do_child();
  }

  return do_parent(pid);  
}
