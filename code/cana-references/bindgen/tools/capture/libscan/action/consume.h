#ifndef __ACTION_CONSUME_H__
#define __ACTION_CONSUME_H__

#include "libscan/action/must.h"
#include "libscan/plugin/consumer.h"

#include "libpepper/unique.hpp"

namespace tokens {
  namespace action {
    namespace consume {
      class object : public must::object {
        public:
          object(std::size_t off);
          virtual ~object() = default;

        private:
          std::size_t off_;

        private:
          unique::vector<plugin::consumer::object> consumers_;
        public:
          void add(plugin::consumer::object *consumer);

        public:
          virtual void perform(cursor &c);
      };
    
      class factory : public must::factory {
        private:
          std::size_t off_;          

        public:
          factory(std::size_t off);
          virtual ~factory() = default;

        private:
          std::vector<plugin::consumer::factory *> factories_;
        public:
          void add(plugin::consumer::factory *factory);

        public:
          virtual tokens::action::must::object *create(void);
      };
    }
  }
}

#endif
