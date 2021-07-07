#include "libscan/action/registry.h"

#include "libscan/action/consume.h"
#include "libscan/action/match.h"

namespace tokens {
  namespace action {
    namespace registry {
      namespace configurators {
        consume::consume(const pepper::named<tokens::plugin::consumer::factory> &cr) : cr_(cr) {
          // DO NOTHING 
        }
        
        void consume::extend(tokens::action::registry::object &r, const boost::property_tree::ptree &pt) {
          std::string name  = pt.get<std::string>("name");
          std::size_t off   = pt.get<std::size_t>("offset");

          auto ptr = new tokens::action::consume::factory(off);

          auto range = pt.equal_range("consumer");

          for (auto it = range.first; it != range.second; ++it) {
            ptr->add( cr_.lookup(it->second.data()) ); 
          }

          r.must_.enroll(name, ptr);
        }

        match::match(const pepper::named<tokens::plugin::matcher::factory> &mr) : mr_(mr) {
          // DO NOTHING;
        }

        void match::extend(tokens::action::registry::object &r, const boost::property_tree::ptree &pt) {
          std::string name    = pt.get<std::string>("name");
          std::string regex   = pt.get<std::string>("regex");

          auto ptr = new tokens::action::match::factory(regex);

          auto range = pt.equal_range("matcher");

          for (auto it = range.first; it != range.second; ++it) {
            auto factory = mr_.lookup(it->second.data());

            assert( factory != nullptr );

            ptr->add(factory);
          }

          r.may_.enroll(name, ptr);
        }
      }
    }
  }
}

