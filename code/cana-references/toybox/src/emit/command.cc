#include "command.h"

#include <unistd.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <iostream>

static unsigned long tick(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);

  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/** Command */
Command::Command()  { }
    
Command::Command(const SyscallContext& ctxt, const char *path, const char **arg, const char **env)
{
  update(ctxt, path, arg, env);
}

Command::~Command() { }

void Command::update(const SyscallContext& ctxt, const char *path, const char **arg, const char **env)
{
  cwd_ = ctxt.cwd();
  exe_ = ctxt.stringAt(path);
  arg_ = ctxt.stringArrayAt(arg);
  env_ = ctxt.stringArrayAt(env);
}

const std::string& Command::cwd(void) const
{
  return cwd_;
}

const std::string& Command::exe(void) const 
{ 
  return exe_; 
}

const std::vector<std::string>& Command::arg(void) const 
{ 
  return arg_; 
}

const std::vector<std::string>& Command::env(void) const 
{ 
  return env_; 
}

void Command::setStart(void) 
{ 
  tStart_ = tick(); 
}

long Command::getStart(void) const 
{ 
  return tStart_; 
}

void Command::setFinish(void) 
{ 
  tFinish_ = tick(); 
}

long Command::getFinish(void) const 
{ 
  return tFinish_; 
}

HIBERLITE_EXPORT_CLASS(Command);

/**
 *
 */
CompileCommand::CompileCommand()
{
  // Do NOTHING
}

CompileCommand::~CompileCommand()
{
  // Do NOTHING
}
