#include "query/list_failure.h"

#include "emit/failure.h"

#include <iostream>

ListFailureMode::ListFailureMode()  { }
ListFailureMode::~ListFailureMode() { }

void ListFailureMode::run(Emit& emit, int argc, char **argv)
{
  auto vec = emit.enumerate<Failure>();

  std::cout << "There are " << vec.size() << " failures:" << std::endl;

  for (hiberlite::bean_ptr<Failure> bean : vec)
  {
    std::cout << "[ id = '" << bean.get_id() << "'; cmd = '" << bean->cmd() << "'; opt = '" << bean->opt() << "' ]" << std::endl;
  }
}
