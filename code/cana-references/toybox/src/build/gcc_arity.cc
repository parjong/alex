#include "build/gcc_arity.h"

GNUArity::GNUArity()
{
  arities_["-c"] = 1;
}

int GNUArity::lookup(const std::string& opt)
{
  auto it = arities_.find(opt);

  if ( it == arities_.end() )
  {   
    return 0;
  }

  return it->second;
}

GNUArity& GNUArity::instance()
{
  static GNUArity obj;
  return obj;
}
