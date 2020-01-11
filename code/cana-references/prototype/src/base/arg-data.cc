#include "arg-data.h"

#include <string.h>

arg_tail::arg_tail() { }

arg_data::arg_data() { }
arg_data::arg_data(char * const *argv)
{
  for (char * const *cur = argv; *cur; ++cur)  
    opts_.push_back( *cur );  
}

void arg_data::push_back(const std::string& opt)
{
  opts_.push_back(opt);
}

char **arg_data::data(void) const 
{
  char **ret = (char **) calloc(opts_.size() + 1, sizeof(char *));

  char **cur = ret;

  for (const std::string& str : opts_)
  {
    *(cur++) = strdup( str.data() );  
  }

  *cur = NULL;

  return ret;
}

arg_tail arg_data::tl(void) const
{
  arg_tail ret;

  auto it = opts_.cbegin();

  if ( it == opts_.cend() )
  {
    return ret;
  }
    
  it++; // SKIP THE FIRST

  for (; it != opts_.cend(); ++it)    
    ret.push_back( *it );      

  return ret;
}
