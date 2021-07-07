#include "monitor/ptrace/ptrace-monitor.h"

#include "base/debug-tools.h"

#include <string.h>
#include <sys/ptrace.h>

#include <set>

static debug::logger file_logger = debug::logger::instance().get_child(__FILE__);

class followee;
class follower;

class followee
{
  public:
    followee() : entered_(false) { }
    ~followee() { }    
  private:
    bool entered_;
  public:
    bool entered(void) const { return entered_; }
    void toggle(void) { entered_ = !entered_; }
  private:
    std::set<follower *> followers_;
  public:
    void append(follower& f) { followers_.insert( &f ); }
    void remove(follower& f) { followers_.erase( &f ); }
  public:
    bool followed(void) const { return followers_.size() > 0; }
};

class follower
{
  public:
    follower() { }
    ~follower() { }
};

class manager
{
  public:
    manager() { }
    ~manager() 
    { 
      for (auto it = followees_.begin(); it != followees_.end(); ++it)
      {
        delete it->second;
      }    
    }
  private:
    std::map<pid_t, followee *> followees_;
  public:
    followee& init_followee(pid_t pid)
    {
      followee *obj = new followee();

      followees_[pid] = obj;

      return *obj;
    }

    void free_followee(pid_t pid)
    {
      auto it = followees_.find(pid);

      if ( it == followees_.end() ) return;

      delete it->second;
    }

    followee *find_followee(pid_t pid)
    {
      auto it = followees_.find(pid);

      if ( it == followees_.end() )
        return nullptr;

      return it->second;
    }

    size_t size_followee(void) const { return followees_.size(); }
  private:
    std::map<pid_t, follower> followers_;
  public:

};

monitor::monitor() { }
monitor::~monitor() { }

void monitor::add(observer& o) 
{ 
  observers_.push_back( &o ); 
}

void monitor::trace(pid_t child) const
{
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  long opts = 0;
  
  opts |= PTRACE_O_TRACEEXEC;
  opts |= PTRACE_O_TRACEEXIT;
  opts |= PTRACE_O_TRACECLONE;
  opts |= PTRACE_O_TRACEFORK;
  opts |= PTRACE_O_TRACEVFORK;
  opts |= PTRACE_O_TRACESYSGOOD;

  /** Wait until ptrace(PTRACE_TRACEME, 0, NULL, NULL) is being executed at the child */
  waitpid(child, NULL, 0);

  if ( ptrace(PTRACE_SETOPTIONS, child, NULL, opts) < 0 )
  {
    LOG_ERROR( func_logger, "ptrace(SETOPTIONS, " << child << ", NULL, " << opts << ") failed: " << strerror(errno) );
    return;
  }
  
  manager m;

  m.init_followee(child);

  /** Continue after setting options */
  ptrace(PTRACE_SYSCALL, child, NULL, NULL);   

  while ( m.size_followee() > 0 )
  {
    int status = 0;

    pid_t curr = waitpid(-1, &status, __WALL);

    /** 1. Is it followee? */
    followee *ee = m.find_followee(curr);
    
    if ( ee != nullptr )
    {
      if ( WIFEXITED(status) )
      {
        LOG_DEBUG( func_logger, "** PID " << curr << " exited" );

        m.free_followee(curr);

        for (observer *o : observers_)       
          o->on_exited(curr);      

        continue;
      }

      if ( WIFSIGNALED(status) ) 
      { 
        LOG_DEBUG( func_logger, "** PID " << curr << " signalled" );

        m.free_followee(curr);

        for (observer *o : observers_) 
          o->on_signaled(curr);

        continue;
      }

      if ( WIFCONTINUED(status) ) 
      {
        LOG_DEBUG( func_logger, "** PID " << curr << " continued" );

        continue;
      }

      if ( !WIFSTOPPED(status) )
      {
        LOG_DEBUG( func_logger, "** PID " << curr << " error!!" );
        continue;
      }

      if ( status >> 8 == (SIGTRAP | 0x80) )
      {
        /** CASE: syscall */
        struct user_regs_struct regs;

        ptrace(PTRACE_GETREGS, curr, NULL, &regs);

        if ( ee->entered() )
        {
          for (observer *o : observers_) 
            o->on_leave(curr, regs);
        }
        else
        {
          for (observer *o : observers_) 
            o->on_enter(curr, regs);         
        }

        ee->toggle();

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status >> 8 == (SIGTRAP | (PTRACE_EVENT_FORK << 8)) )
      {
        pid_t next;
        ptrace(PTRACE_GETEVENTMSG, curr, NULL, &next);

        LOG_DEBUG( func_logger, "** PID " << next << " forked" );

        m.init_followee(next);

        for (observer *o : observers_) 
          o->on_fork(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status>>8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)) )
      {
        pid_t next;
        ptrace(PTRACE_GETEVENTMSG, curr, NULL, &next);

        LOG_DEBUG( func_logger, "** PID " << next << " cloned" );

        m.init_followee(next);       

        for (observer *o : observers_) 
          o->on_clone(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status>>8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)) )
      {
        pid_t next;
        ptrace(PTRACE_GETEVENTMSG, curr, NULL, &next);

        LOG_DEBUG( func_logger, "** PID " << next << " vforked" );

        m.init_followee(next);       

        for (observer *o : observers_) 
          o->on_vfork(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status>>8 == (SIGTRAP | (PTRACE_EVENT_VFORK_DONE<<8)) )
      {
        for (observer *o : observers_) 
          o->on_vfork_done(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status>>8 == (SIGTRAP | (PTRACE_EVENT_EXEC<<8)) )
      {
        for (observer *o : observers_) 
          o->on_exec(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }
      else if ( status>>8 == (SIGTRAP | (PTRACE_EVENT_EXIT<<8)) )
      {
        for (observer *o : observers_) 
          o->on_exit(curr);

        ptrace(PTRACE_SYSCALL, curr, NULL, NULL);   
        continue;
      }

      ptrace(PTRACE_SYSCALL, curr, NULL, WSTOPSIG(status));   
      continue;      
    }

    /** Otherwise */
    continue;
  }
}

