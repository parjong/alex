#include <pepper/env/system/setter/spec.hpp>

#include <cstdlib>

namespace pepper { namespace env { namespace system { namespace setter {
  
  spec::spec(const std::string &key) : _key{key}
  {
    // DO NOTHING
  }
      
  void spec::set(const std::string &value)
  {
    setenv(_key.c_str(), value.c_str(), 1); 
  }

} } } }
