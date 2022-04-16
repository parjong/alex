#include "query/list_file.h"

#include "emit/code.h"

#include <iostream>

ListFileMode::ListFileMode()  { }
ListFileMode::~ListFileMode() { }

void ListFileMode::run(Emit& emit, int argc, char **argv)
{
  auto vec = emit.enumerate<Code>();

  std::cout << "There are " << vec.size() << " sources:" << std::endl;

  for (hiberlite::bean_ptr<Code> bean : vec)
  {
    std::cout << "[ id = '" << bean.get_id() << "'; cmd = '" << bean->cmd() << "'; lines = '" << bean->lines().size() << "' ]" << std::endl;
  }
}
