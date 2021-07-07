#include "libscan/action/match.h"

namespace tokens {
  namespace action {
    namespace match {
      object::object(const std::string &re) : re_(re.c_str()) {
        // DO NOTHING
      }

      void object::add(plugin::matcher::object *matcher) {
        matchers_.emplace_back(matcher);
      }

      bool object::perform(cursor &c) {
        assert( c.lookup(0) );

        boost::smatch sm;

        if ( !boost::regex_match(c.lookup(0).get(), sm, re_) ) {
          return false;
        }

        for (auto &matcher : matchers_) {
          matcher->match(sm);
        }

        c.forward(1);
        return true;
      }

      factory::factory(const std::string &regex) : regex_(regex) {
        // DO NOTHING
      }

      void factory::add(plugin::matcher::factory *factory) {
        factories_.push_back(factory);
      }

      may::object *factory::create(void) {
        object *obj = new object(regex_);

        for (auto &factory : factories_) {
          obj->add(factory->create());
        }

        return obj;
      }
    }
  }
}

