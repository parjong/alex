#ifndef BC_PTRACE_MONITOR_H__
#define BC_PTRACE_MONITOR_H__

#include <vector>

#include "monitor/ptrace/ptrace-observer.h"

class monitor 
{
  public:
    monitor();
    ~monitor();
  private:
    std::vector<observer *> observers_;
  public:
    void add(observer& o);  
  public:
    void trace(pid_t child) const; 
};

#endif
