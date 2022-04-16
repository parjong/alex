#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <map>
#include <string>
#include <vector>

#include "cursor.h"
#include "action/must.h"
#include "action/may.h"

#include "libpepper/named.hpp"
#include "libpepper/unique.hpp"

#include "libscan/action/registry.h"

#include "libpepper/configure.hpp"

namespace tokens {
  namespace scanner {
    class object {
      public:
        object() = default;
        ~object() = default;

      private:
        pepper::named<action::must::object> must_actions_;
      public:
        void add(const std::string& tag, action::must::object *act);           

      private:
        unique::vector<action::may::object> may_actions_;
      public:
        void add(action::may::object *act);

      private:
        bool try_must(cursor &c) const;
        bool try_may(cursor &c) const;
      public:
        void scan(cursor &c);
    };           

    namespace configurators {
      class may : public configure::action<object> {
        private:
          const tokens::action::registry::object &r_;

        public:
          may(const tokens::action::registry::object &r);
          virtual ~may() = default;

        public:
          virtual void extend(object &s, const boost::property_tree::ptree &pt);
      };

      class must : public configure::action<object> {
        private:
          const tokens::action::registry::object &r_;

        public:
          must(const tokens::action::registry::object &r);
          virtual ~must() = default;

        public:
          virtual void extend(object &s, const boost::property_tree::ptree &pt);
      };
    }
  }
}

#endif
