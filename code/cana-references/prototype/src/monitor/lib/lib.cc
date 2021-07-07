#include "base/owned.hpp"
#include "base/debug-tools.h"

#include "monitor/lib/api.h"
#include "monitor/lib/wrap.h"
#include "monitor/lib/filename-tools.h"

#include "plugin/init.h"

static debug::logger file_logger = debug::logger::instance().get_child(__FILE__);

extern char **environ;

__attribute__((constructor)) static void init(void)
{
  setup();
  debug::manager::init();
}

__attribute__((constructor)) static void hook_execve(void)
{
  _execve_api.hook();
}

extern "C" int execv(const char *path, char * const argv[])
{ 
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  LOG_INFO( func_logger, "execv(" << path << ")" );

  return execve_wrap(path, argv, environ);
}

extern "C" int execvp(const char *file, char * const argv[])
{ 
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);

  LOG_INFO( func_logger, "execvp(" << file << ")" );

  owned<char> path( filename_tools::resolve(file), free );
  return execve_wrap(path, argv, environ);
}

extern "C" int execve(const char *path, char * const argv[], char * const envp[])
{  
  static debug::logger func_logger = file_logger.get_child(__FUNCTION__);
  
  LOG_INFO( func_logger, "execve(" << path << ")" );
  
  return execve_wrap(path, argv, envp);
}
