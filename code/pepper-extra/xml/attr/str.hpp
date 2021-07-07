#ifndef __PEPPER_XML_ATTR_STR_H__
#define __PEPPER_XML_ATTR_STR_H__

#include "pepper/opt.hpp"
#include "pepper/xml/attr/base.hpp"

namespace pepper { namespace xml { namespace attr { 

  class str : public base
  {
    private:
      pepper::opt<std::string> _value;

    public:
      str(xml::elem &e, const std::string &name);
      virtual ~str() = default;

    public:
      void set(const std::string &value);
      const std::string &get(void) const;

    public:
      str &operator=(const std::string &value);

    public:
      virtual void set_attribute(xmlNodePtr node);
      virtual bool is_initialized(void) const;
  };

} } }

#endif
