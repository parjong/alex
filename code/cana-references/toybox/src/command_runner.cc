#include "command_runner.h"

#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/wait.h>

static char **convert(const std::vector<std::string>& vec)
{
  int     cnt = 0;
  char**  ptr = (char **) calloc(vec.size() + 1, sizeof(char *));

  for (const std::string& str : vec)
  {
    ptr[cnt++] = strdup(str.c_str());
  }

  ptr[cnt] = NULL;

  return ptr;
}

/**
 *
 */
CommandRunner::CommandRunner() { }
CommandRunner::~CommandRunner() { }

/**
 *
 */
ExecCommandRunner::ExecCommandRunner() { }
ExecCommandRunner::~ExecCommandRunner() { }

void ExecCommandRunner::run(const std::string& cwd, const std::string& exe, const std::vector<std::string>& arg, const std::vector<std::string>& env)
{
  assert( chdir(cwd.c_str()) == 0 );
 
  char *path  = strdup(exe.c_str());
  char **argv = convert(arg);
  char **envp = convert(env);

  execve(path, argv, envp);

  assert( 0 && "execve failed" );
}

/**
 *
 */
ForkCommandRunner::ForkCommandRunner() 
  : rdout_(nullptr)
{ 

}

void ForkCommandRunner::redirectOutput(FILE *out)
{
  rdout_ = out;
}

ForkCommandRunner::~ForkCommandRunner() { }

void ForkCommandRunner::run(const std::string& cwd, const std::string& exe, const std::vector<std::string>& arg, const std::vector<std::string>& env)
{
  pid_t pid = fork();

  assert( pid != -1 );

  if ( pid == 0 )
  {
    if ( rdout_ != nullptr )
    {
      assert( dup2(fileno(rdout_), 1) != -1 );
    }

    ExecCommandRunner runner;

    runner.run(cwd, exe, arg, env);
  }
  
  waitpid(pid, NULL, 0);
}
