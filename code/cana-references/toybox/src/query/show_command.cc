#include "query/show_command.h"

#include "emit/command.h"

#include <iostream>

ShowCommandMode::ShowCommandMode()  { }
ShowCommandMode::~ShowCommandMode() { }

void ShowCommandMode::run(Emit& emit, int argc, char **argv)
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

      std::cout << "ID:     " << id << std::endl;
      std::cout << "CWD:    " << bean->cwd() << std::endl;
      std::cout << "EXE:    " << bean->exe() << std::endl;

      std::cout << "ARG:    " << std::endl;
      for (const std::string& arg : bean->arg())
      {
        std::cout << "  " << arg << std::endl;
      }

      std::cout << "ENV:    " << std::endl;
      for (const std::string& arg : bean->env())
      {
        std::cout << "  " << arg << std::endl;
      }

      std::cout << "BEGIN:  " << bean->getStart() << std::endl;
      std::cout << "FINISH: " << bean->getFinish() << std::endl;
      curr += 2;
    }
    else
    {
      break;
    }
  }
}
