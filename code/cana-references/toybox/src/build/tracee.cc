#include "tracee.h"

#include <unistd.h>

Tracee::Tracee() { }
Tracee::~Tracee() { }

ExecTracee::ExecTracee(const char *path, char * const *argv, char * const *envp)
  : path_(path), argv_(argv), envp_(envp)
{ } 

ExecTracee::~ExecTracee() { }

void ExecTracee::run(void) 
{
  execve(path_, argv_, envp_);
}
