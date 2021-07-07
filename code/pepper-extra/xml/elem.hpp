#ifndef __PEPPER_XML_ELEM_H__
#define __PEPPER_XML_ELEM_H__

#include "pepper/opt.hpp"
#include "pepper/xml/attr/base.forward.hpp"

#include <memory>
#include <string>
#include <vector>
#include <libxml/tree.h>

namespace pepper { namespace xml {

    class elem
    {
      public:        
        elem(const std::string &name);
        virtual ~elem() = default;
 
      private:
        std::string _name;
      public:
        const std::string &name(void) const;
    
      private:
        pepper::opt<std::string> _text;
      public:
        void set_text(const std::string &text);

      private:
        std::vector<xml::attr::base *> _attrs;
      public:        
        void add_attr(xml::attr::base &);

      private:
        std::vector<std::unique_ptr<elem>> _children;       
      public:
        template <typename T> T &add_elem(T *child)
        {
          _children.emplace_back(child);
          return *child;
        }

      public:
        template <typename T, typename... Args> T &create_elem(const Args&... args)
        {
          return this->add_elem( new T{ args...} );
        }

      public:
        void write_into(xmlNodePtr node);
    };
    
    std::ostream &operator<<(std::ostream &os, elem &elem);
  
} }

#endif
