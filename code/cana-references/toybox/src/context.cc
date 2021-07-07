#include "context.h"

#include <assert.h>
#include <sys/ptrace.h>
#include <sys/user.h>

Context::Context()  { }
Context::~Context() { }

/**
 *
 */
EventContext::EventContext(pid_t pid) 
  : pid_(pid)
{ }
EventContext::~EventContext() { }

pid_t EventContext::pid(void) const { return pid_; }

/**
 *
 */
ExitedEventContext::ExitedEventContext(pid_t pid) 
  : EventContext(pid) { }
ExitedEventContext::~ExitedEventContext() { }

/** 
 *
 */
ExecEventContext::ExecEventContext(pid_t pid) 
  : EventContext(pid) { }
ExecEventContext::~ExecEventContext() { }


/**
 *
 */
SyscallContext::SyscallContext(pid_t pid)
  : pid_(pid)
{
  assert( ptrace(PTRACE_GETREGS, pid_, NULL, &regs_) != -1 );
}

SyscallContext::~SyscallContext() { }

pid_t SyscallContext::pid(void) const { return pid_; }
const user_regs_struct& SyscallContext::regs(void) const { return regs_; }

std::string SyscallContext::cwd(void) const 
{
  char *cwd = nullptr;
  char *resolved = nullptr;

  asprintf(&cwd, "/proc/%d/cwd", pid_);
  resolved = realpath(cwd, NULL);

  std::string res(resolved);

  free(resolved);
  free(cwd);

  return res;
}

long SyscallContext::wordAt(const char *addr) const
{
  return ptrace(PTRACE_PEEKDATA, pid_, addr, NULL);
}

std::string SyscallContext::stringAt(const char *addr) const
{
  std::string ret;

  const char *cur = addr;

  while (1)
  {
    long value = wordAt(cur);

    const char *ptr = (const char *) &value;

    size_t idx = 0;
    size_t len = sizeof(value);

    for (idx = 0; idx < len && ptr[idx] != '\0'; ++idx)
    {
      ret.push_back(ptr[idx]);
    }

    if ( idx < len ) break;

    cur += len;
  }

  return ret;
}

std::vector<std::string> SyscallContext::stringArrayAt(const char **addr) const
{
  std::vector<std::string> ret;

  const char **cur = addr;

  while (1)
  {
    const char *ptr = (const char *) wordAt((const char *) cur);

    if ( ptr == NULL ) break;

    ret.push_back( stringAt(ptr) );

    ++cur;
  }

  return ret;
}

/**
 *
 */
EnterEventContext::EnterEventContext(pid_t pid) 
  : SyscallContext(pid) { }
EnterEventContext::~EnterEventContext() { }

/**
 *
 */
LeaveEventContext::LeaveEventContext(pid_t pid) 
  : SyscallContext(pid) { }
LeaveEventContext::~LeaveEventContext() { }
