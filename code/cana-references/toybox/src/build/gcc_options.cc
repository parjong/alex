#include "build/gcc_options.h"

GNUOptions::GNUOptions()  
{ 
  // Do NOTHING
}

GNUOptions::~GNUOptions()
{
  for (GNUOption *option : options_)
  {
    delete option;
  }
}

void GNUOptions::append(GNUOption *arg)
{
  options_.push_back(arg);
}

void GNUOptions::accept(GNUOptionVisitor& v) const
{
  for (GNUOption *option : options_)
  {
    option->accept(v);
  }
}
