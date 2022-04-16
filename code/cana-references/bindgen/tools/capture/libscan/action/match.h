#ifndef __ACTION_MATCH_H__
#define __ACTION_MATCH_H__

#include "libscan/action/may.h"
#include "libscan/plugin/matcher.h"

#include "libpepper/unique.hpp"

#include <boost/regex.hpp>

namespace tokens {
  namespace action {
    namespace match {
      class object : public may::object {
        public:
          object(const std::string &re);
          virtual ~object() = default;

        private:
          boost::regex re_;

        private:
          unique::vector<plugin::matcher::object> matchers_;
        public:
          void add(plugin::matcher::object *matcher);

        public:
          virtual bool perform(cursor &c);
      };

      class factory : public may::factory {
        private:
          const std::string regex_;

        public:
          factory(const std::string &regex);
          virtual ~factory() = default;

        private:
          std::vector<plugin::matcher::factory *> factories_;
        public:
          void add(plugin::matcher::factory *factory);

        public:
          virtual may::object *create(void); 
      };
    }
  }
}

#endif
