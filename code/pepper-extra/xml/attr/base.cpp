#include "pepper/xml/attr/base.hpp"

#include "pepper/logging.hpp"

namespace pepper { namespace xml { namespace attr { 
    
  base::base(elem &e, const std::string &name)
    : _name{ name }      
  {
    e.add_attr(*this);
  }

  const std::string &base::name(void) const
  {
    return _name;
  }

} } }
