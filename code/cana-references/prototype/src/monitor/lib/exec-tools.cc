#include "monitor/lib/exec-tools.h"
#include "monitor/lib/api.h"

#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

/** Destructor? */
class buffer
{
  public:
    buffer() : ptr_(nullptr) { }
    buffer(char **ptr) : ptr_(ptr) { }
  public:
    ~buffer()
    {
      for (char * const *cur = ptr_; *cur; ++cur)      
      {
        free(*cur);      
      }

      free(ptr_);
    }
  private:
    char **ptr_;
  public:
    char * const *data(void) const { return ptr_; }
};

int run_in_current(const std::string& path, const arg_data& arg, const env_data& env)
{
  buffer argv( arg.data() );
  buffer envp( env.data() );

  return _execve_api.invoke(path.data(), argv.data(), envp.data());
}

child_status_t run_at_child(const std::string& path, const arg_data& arg, const env_data& env, int *retcode)
{
  pid_t pid = fork();

  if ( pid == -1 ) 
  {
    return CHILD_FAILED;
  }

  if ( pid == 0 )
  {
    run_in_current(path, arg, env);
    exit(127);
  }

  int status;
     
  while (1)
  {
    if ( waitpid(pid, &status, 0) == pid ) 
    {
      if ( WIFEXITED(status) ) 
      {
        if ( retcode != nullptr )
          *retcode = WEXITSTATUS(status);
        return CHILD_EXITED;
      }

      if ( WIFSIGNALED(status) )
      {
        if ( retcode != nullptr )        
          *retcode = WTERMSIG(status);
        return CHILD_SIGNALED;
      }
    }
  }  

  return CHILD_FAILED;
}
