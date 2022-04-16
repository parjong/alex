#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include "named.hpp"

#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>

namespace configure {
  template <typename T> struct action {
    action() = default;
    virtual ~action() = default;

    virtual void extend(T &object, const boost::property_tree::ptree &pt) = 0;
  };
}

namespace configure {
  template <typename T> class configurator {  
    private:
      pepper::named<action<T>> r_;
    public:
      configurator() = default;
      ~configurator() = default;

    public:
      configurator &enroll(const std::string &name, action<T> *ext) {
        r_.enroll(name, ext);
      }

    public:
      void configure(T &obj, const boost::property_tree::ptree &pt) {
        for (auto child : pt) {
          action<T> *ext = r_.lookup(child.first);

          if ( ext == nullptr ) {        
            boost::format fmt("'%s' is not supported");

            throw std::runtime_error(boost::str(fmt % child.first));
          }

          ext->extend(obj, child.second);
        }
      }
  };
}


#endif
