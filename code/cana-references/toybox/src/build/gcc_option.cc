#include "build/gcc_option.h"

/**
 *
 */
GNUOption::GNUOption() { }
GNUOption::~GNUOption() { }

/**
 *
 */
GNUOptionVisitor::GNUOptionVisitor()  { }
GNUOptionVisitor::~GNUOptionVisitor() { }

/**
 *
 */
GNUIncludeOption::GNUIncludeOption(const std::string& dir) 
  : dir_(dir)
{
  // Do NOTHING
}

GNUIncludeOption::~GNUIncludeOption() { }

const std::string& GNUIncludeOption::dir(void) const 
{ 
  return dir_;
}

void GNUIncludeOption::accept(GNUOptionVisitor& v) const
{
  v.visit(*this);
}

/**
 *
 */
GNUDefineOption::GNUDefineOption(const std::string& def) 
  : def_(def)
{
  // Do NOTHING
}

GNUDefineOption::~GNUDefineOption()
{
  // Do NOTHING
}

const std::string& GNUDefineOption::def(void) const
{
  return def_;
}

void GNUDefineOption::accept(GNUOptionVisitor& v) const
{
  v.visit(*this);
}
