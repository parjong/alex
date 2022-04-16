#include "pepper/xml/elem.hpp"
#include "pepper/xml/attr/base.hpp"

#include "pepper/logging.hpp"

namespace pepper { namespace xml {    
  
  elem::elem(const std::string &name)
    : _name{ name }
  {
    // DO NOTHING
  }

  const std::string &elem::name(void) const
  {
    return _name;
  }

  void elem::set_text(const std::string &text)
  {
    _text = text;
  }

  void elem::add_attr(attr::base &attr)
  {
    static pepper::logging::logger log{ "pepper.xml.elem.add_attr" };

    log.debug( "add attr %s", attr.name() );

    _attrs.push_back( &attr );
  }

  void elem::write_into(xmlNodePtr curr)
  {
    for (auto attr : _attrs)
    {
      attr->set_attribute(curr);
    }

    for (auto &child : _children)
    {       
      xmlNodePtr next = xmlNewNode( nullptr, (const xmlChar *) child->name().c_str() );     
      xmlAddChild( curr, next );      
      child->write_into(next);
    }

    auto set_fn = [&] (const std::string &value)
    {
      xmlNodePtr child = xmlNewText( (const xmlChar *) value.c_str() );
      xmlAddChild( curr, child );
    };

    _text.map(set_fn);
  }

  std::ostream &operator<<(std::ostream &os, elem &e)
  {
    xmlNodePtr xmlNode = xmlNewNode( nullptr, (const xmlChar *) e.name().c_str() );

    e.write_into(xmlNode);

    xmlChar *buff_ptr = nullptr;
    int      buff_len = -1;

    xmlDocPtr xmlDoc = xmlNewDoc( (const xmlChar *) "1.0" );
    xmlDocSetRootElement( xmlDoc, xmlNode );
    xmlDocDumpFormatMemory(xmlDoc, &buff_ptr, &buff_len, 1);

    os << buff_ptr;

    xmlFree(buff_ptr);
    xmlFreeDoc( xmlDoc );

    return os;
  }
  
} }
