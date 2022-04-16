#include <pepper/tokens/tokens.h>

#include <pepper/tokens/action/consume.h>

namespace pepper {
  namespace tokens {
    configurator::configurator(context &ctxt) : ctxt_(ctxt) {

    }
    
    configurator::~configurator() {
      // DO NOTHING
    }

    action::base *select(const std::string &type) {      
      if (type == "consume(1)")
        return new action::consume<1>();
      if (type == "consume(2)") 
        return new action::consume<2>();      
      throw "invalid type";
    }

    void configurator::read_action(const boost::property_tree::ptree &pt) {
      std::string name = pt.get<std::string>("name");
      std::string type = pt.get<std::string>("type");

      ctxt_.add_action(name, select(type));
    }

    void configurator::read_tag(scanner *ptr, const boost::property_tree::ptree &pt) {
      std::string value   = pt.get<std::string>("value");
      std::string action  = pt.get<std::string>("action");

      ptr->add(value, ctxt_.get_action(action));
    }

    scanner *configurator::configure(const boost::property_tree::ptree &pt) {
      /* Read 'actions' section */
      for (auto &child : pt.get_child("actions")) {
        if ( child.first == "action" ) {
          read_action(child.second);
        }
      }

      std::unique_ptr<scanner> ptr( new scanner() );
      
      /* Read 'scanner' section */
      for (auto &child : pt.get_child("scanner")) {
        if ( child.first == "tag" ) {
          read_tag(ptr.get(), child.second);
        }
      }

      return ptr.release();
    }
  }
}
