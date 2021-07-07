#ifndef BC_PTRACE_OBSERVER_H__
#define BC_PTRACE_OBSERVER_H__

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

class observer
{
  public:
    observer();
    virtual ~observer();
  public:
    virtual void on_exited(pid_t child) = 0;
    virtual void on_signaled(pid_t child) = 0;

    virtual void on_fork(pid_t child) = 0;
    virtual void on_clone(pid_t child) = 0;
    virtual void on_vfork(pid_t child) = 0;
    virtual void on_vfork_done(pid_t child) = 0;
    virtual void on_exit(pid_t child) = 0;
    virtual void on_exec(pid_t child) = 0;

    virtual void on_enter(pid_t child, struct user_regs_struct& reg) = 0;
    virtual void on_leave(pid_t child, struct user_regs_struct& reg) = 0;   
};


#endif
