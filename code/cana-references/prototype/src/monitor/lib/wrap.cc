#include "monitor/lib/wrap.h"

#include "base/path-data.h"
#include "base/distrib-data.h"

#include "monitor/lib/api.h"
#include "monitor/lib/exec-tools.h"
#include "monitor/lib/linux-system.h"
#include "monitor/lib/hook.h"

#include "plugin/manager.h"

#include <signal.h>

#include <string>
#include <memory>

int execve_wrap(const char *filename, char * const argv[], char * const envp[])
{ 
  std::unique_ptr<distrib_data> dist( distrib_data::build() );

  if ( dist == nullptr )
  {
    return _execve_api.invoke(filename, argv, envp);
  }

  const path_data path(filename);
  const arg_data  arg(argv);
  const env_data  env(envp);

  arg_data arg_( arg );
  env_data env_( env );

  hook::libc_plugin libc_hook( *dist );

  const actor *act = manager::instance().lookup(path.normalized());

  if ( act != NULL )
  {    
    int code = 0;
    
    libc_hook.disable( env_ );

    child_status_t status = run_at_child(path.provided(), arg_, env_, &code);

    if ( status == CHILD_FAILED )
    {
      exit(127);
    }

    char *wd = get_current_dir_name();

    linux_system lp;

    act->perform(lp, wd, path.normalized(), arg_, env_);

    if ( status == CHILD_SIGNALED )
    {
      raise(code);
      exit(0);
    }

    exit(code);  
  }

  /** enable LD_PRELOAD hook */
  libc_hook.enable(env_);

  return run_in_current(path.provided(), arg_, env_);
}
