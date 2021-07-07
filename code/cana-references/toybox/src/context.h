#ifndef CONTEXT_H__
#define CONTEXT_H__

#include <string>
#include <vector>

#include <sys/user.h>

class Context
{
  public:
    Context();
    virtual ~Context();
};

class EventContext : public Context
{
  public:
    EventContext(pid_t pid);
    virtual ~EventContext();
  private:
    pid_t pid_;
  public:
    pid_t pid(void) const;
};

class ExitedEventContext : public EventContext
{
  public:
    ExitedEventContext(pid_t pid);
    virtual ~ExitedEventContext();
};

class ExecEventContext : public EventContext
{
  public:
    ExecEventContext(pid_t pid);
    virtual ~ExecEventContext();
};


class SyscallContext : public Context
{
  public:
    SyscallContext(pid_t pid);
    virtual ~SyscallContext();
  private:
    pid_t pid_;
    struct user_regs_struct  regs_;
  public:
    pid_t pid(void) const;
    const struct user_regs_struct& regs(void) const;
  public:
    std::string cwd(void) const;
  public:
    long wordAt(const char *addr) const;
    std::string stringAt(const char *addr) const;    
    std::vector<std::string> stringArrayAt(const char **addr) const;
};

class EnterEventContext : public SyscallContext
{
  public:
    EnterEventContext(pid_t pid);
    virtual ~EnterEventContext();
};

class LeaveEventContext : public SyscallContext
{
  public:
    LeaveEventContext(pid_t pid);
    virtual ~LeaveEventContext();
};

#endif
