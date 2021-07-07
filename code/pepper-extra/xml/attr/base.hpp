#ifndef __PEPPER_XML_ATTR_BASE_H__
#define __PEPPER_XML_ATTR_BASE_H__

#include "pepper/xml/elem.hpp"

namespace pepper { namespace xml { namespace attr {
    
  class base
  {
    private:
      std::string _name;

    public:
      base(xml::elem &e, const std::string &name);
      virtual ~base() = default;

    public:
      const std::string &name(void) const;

    public:
      virtual void set_attribute(xmlNodePtr node) = 0;
      virtual bool is_initialized(void) const = 0;
  };

} } }

#endif
