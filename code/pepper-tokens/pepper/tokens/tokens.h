#ifndef __PEPPER_TOKENS_H__
#define __PEPPER_TOKENS_H__

#include <pepper/tokens/scanner.h>
#include <boost/property_tree/ptree.hpp>

namespace pepper {
  namespace tokens {
    class context {
      public:
        context() = default;
        ~context() = default;

      private:
        std::map<std::string, action::base *> actions_;
      public:
        void add_action(const std::string &name, action::base *action) {
          actions_[name] = action;
        }

        action::base *get_action(const std::string &name) const {
          auto it = actions_.find(name);

          if ( it == actions_.end() ) {
            return nullptr;
          }

          return it->second;
        }
    };
  }
}

namespace pepper {
  namespace tokens {
    class configurator {
      private:
        context &ctxt_;

      public:
        configurator(context &ctxt);
        ~configurator();

      private:
        void read_action(const boost::property_tree::ptree &pt);
        void read_tag(scanner *ptr, const boost::property_tree::ptree &pt);

      public:
        scanner *configure(const boost::property_tree::ptree &pt);
    };
  }
}

#endif
