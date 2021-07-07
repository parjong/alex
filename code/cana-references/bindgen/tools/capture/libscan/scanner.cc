#include "scanner.h"

namespace tokens {
  namespace scanner {
    void object::add(const std::string& tag, action::must::object *act) {
      must_actions_.enroll(tag, act);
    }

    void object::add(action::may::object *act) {
      may_actions_.emplace_back(act);
    }

    bool object::try_must(cursor &c) const {
      action::must::object *action = 
        must_actions_.lookup( c.lookup(0).get() );

      if ( action != nullptr ) {
        action->perform(c);
        return true;
      }

      return false;
    }

    bool object::try_may(cursor &c) const {
      for (auto &may_action : may_actions_) {
        if ( may_action->perform(c) ) {
          return true;
        }
      }

      return false;
    }

    void object::scan(cursor &c) {
      while ( c.lookup(0) ) {
        if ( !( try_must(c) || try_may(c) ) ) {
          break;
        }
      }
    }

    namespace configurators {
      may::may(const tokens::action::registry::object &r) : r_(r) { }

      void may::extend(object &s, const boost::property_tree::ptree &pt) {            
        tokens::action::may::object *action =
          r_.may_.lookup( pt.get<std::string>("action") )->create();

        assert( action != nullptr );

        s.add(action);
      }

      must::must(const tokens::action::registry::object &r) : r_(r) { }

      void must::extend(object &s, const boost::property_tree::ptree &pt) {
        std::string value = pt.get<std::string>("value");
        tokens::action::must::object *action =
          r_.must_.lookup( pt.get<std::string>("action") )->create();

        assert( action != nullptr );

        s.add(value, action);
      }
    }
  }
}
