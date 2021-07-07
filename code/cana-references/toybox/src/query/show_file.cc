#include "query/show_file.h"

#include "emit/code.h"

#include <iostream>

ShowFileMode::ShowFileMode()  { }
ShowFileMode::~ShowFileMode() { }

void ShowFileMode::run(Emit& emit, int argc, char **argv)
{
  char **curr = argv;

  while ( *curr )
  {
    char *opt = *curr;

    if ( strcmp(opt, "--id") == 0 )
    {
      char *arg = *(curr + 1);

      int id = atoi(arg);

      hiberlite::bean_ptr<Code> bean = emit.select<Code>(id);

      for (const std::string& line : bean->lines())
      {
        std::cout << line;
      }

      break;
    }
    else
    {
      break;
    }
  } 
}
