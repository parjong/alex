#ifndef MONITOR_H__
#define MONITOR_H__

#include "terminator.h"

#include "tracee.h"
#include "tracer.h"

#include <set>

class SyscallStatus
{
  public:
    SyscallStatus();
    ~SyscallStatus();
  private:
    std::set<pid_t> entered_;
  public:
    void clear(pid_t pid);
    void update(pid_t pid);
    bool check(pid_t pid) const;
};

class Monitor
{
  public:
    Monitor(Tracee& tracee, Tracer& ctl);
    ~Monitor();

  private:
    Tracee&   tracee_;
    Tracer&   tracer_;

  private:
    SyscallStatus status_;

  private:
    void do_child(void);
    Terminator *do_parent(pid_t pid);
  public:
    Terminator *trace(void);
};

#endif
