#include "plugin/checker/basename.h"

basename_checker::basename_checker(const std::string& base) 
  : base_(base)
{ }

basename_checker::~basename_checker() { }

bool basename_checker::check(const std::string& path) const 
{
  size_t pos = path.find_last_of('/');

  if ( pos == std::string::npos )
  {
    return path == base_;
  }

  return path.substr(pos + 1) == base_;
}
