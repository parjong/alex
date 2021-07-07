#include "emit.h"

#include "command.h"
#include "failure.h"
#include "code.h"

Emit::Emit(const std::string& name) 
  : db_(name)
{
  db_.registerBeanClass<Command>();
  db_.registerBeanClass<Failure>();
  db_.registerBeanClass<Code>();
}

Emit::~Emit() { }

void Emit::init(void) 
{
  db_.dropModel();
  db_.createModel();
}
