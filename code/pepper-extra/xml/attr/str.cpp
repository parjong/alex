#include "pepper/xml/attr/str.hpp"

#include "pepper/logging.hpp"

namespace pepper { namespace xml { namespace attr { 

  str::str(elem &e, const std::string &name)
    : base{ e, name }
  {
    // DO NOTHING
  }


  str &str::operator=(const std::string &value)
  {
    this->set(value);
  }

  void str::set(const std::string &value) 
  { 
    static pepper::logging::logger log{ "pepper.xml.str.set" };

    log.debug( "sets attribute %s as %s", name(), value );

    _value = value; 
  }

  const std::string &str::get(void) const 
  { 
    return _value.get(); 
  }

  void str::set_attribute(xmlNodePtr node)
  {
    auto set_fn = [&] (const std::string &value)
    {
      xmlSetProp( node, (const xmlChar *) name().c_str(), 
                        (const xmlChar *) value.c_str() );
    };

    _value.map( set_fn );
  }

  bool str::is_initialized(void) const
  {
    return _value.is_initialized();
  }

} } }
