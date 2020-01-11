#include "api.h"

#include <unistd.h>
#include <dlfcn.h>

#include <iostream>

execve_api::execve_api() : func_(nullptr) { }

bool execve_api::hook(void)
{
  func_ = (func_t) dlsym(RTLD_NEXT, "execve");
}

int execve_api::invoke(const char *filename, char * const argv[], char * const envp[])
{
   if ( func_ == nullptr )      
      return execve(filename, argv, envp);      
   return func_(filename, argv, envp);
}    

execve_api _execve_api;
