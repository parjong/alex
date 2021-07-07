#include "distrib-data.h"

distrib_data::distrib_data(const std::string& base) 
  : base_(base), 
    bin_(base + "/bin"),
    lib_(base + "/lib") 
{ }

const std::string &distrib_data::basedir(void) const { return base_; }
const std::string &distrib_data::bindir(void) const { return bin_; }
const std::string &distrib_data::libdir(void) const { return lib_; }
    
distrib_data *distrib_data::build(void) 
{
  char *value = getenv("BC_DISTRIB_DIR");

  if ( value == nullptr )
    return nullptr;

  return new distrib_data(value);
}
