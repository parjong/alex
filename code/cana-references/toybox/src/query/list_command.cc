#include "query/list_command.h"

#include "emit/command.h"

#include <iostream>

ListCommandMode::ListCommandMode()  { }
ListCommandMode::~ListCommandMode() { }

void ListCommandMode::run(Emit& emit, int argc, char **argv)
{
  auto vec = emit.enumerate<Command>();

  std::cout << vec.size() << " commands are captured:" << std::endl;

  for (hiberlite::bean_ptr<Command> c : vec)
  {
    std::cout << "[ id = '" << c.get_id() << "'; exe = '" << c->exe() << "'; elapsed = '" << c->getFinish() - c->getStart() << "' ]" << std::endl;
  }
}
