#include "query/exec.h"

#include "emit/command.h"

#include "command_runner.h"

ExecuteMode::ExecuteMode()  { }
ExecuteMode::~ExecuteMode() { }

void ExecuteMode::run(Emit& emit, int argc, char **argv)
{
  char **curr = argv;

  while ( *curr )
  {
    char *opt = *curr;

    if ( strcmp(opt, "--id") == 0 )
    {
      char *arg = *(curr + 1);

      int id = atoi(arg);

      hiberlite::bean_ptr<Command> bean = emit.select<Command>(id);

      ExecCommandRunner runner;

      runner.run(bean->cwd(), bean->exe(), bean->arg(), bean->env());

      curr += 2;
    }
    else
    {
      break;
    }
  }
}
