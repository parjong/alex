#include "libscan/action/consume.h"

#include <stdexcept>

namespace tokens {
  namespace action {
    namespace consume {
      object::object(std::size_t off) : off_(off) {
        // DO NOTHING
      }

      void object::add(plugin::consumer::object *consumer) {
        consumers_.emplace_back(consumer);
      }

      void object::perform(cursor &c) {
        std::vector<std::string> vec;

        for (std::size_t i = 0; i < off_; ++i) {
          if ( !c.lookup(0) ) {
            throw std::runtime_error("not enough tokens");
          }

          vec.emplace_back( c.lookup(0).get() );

          c.forward(1);
        }

        for (auto &consumer : consumers_) {
          consumer->consume(vec);
        }
      }

      factory::factory(std::size_t off) : off_(off) { 
        // DO NOTHING
      }

      void factory::add(plugin::consumer::factory *factory) {
        factories_.push_back(factory);
      }

      must::object *factory::create(void) {
        auto ptr = new object(off_);

        for (auto factory : factories_) {
          ptr->add( factory->create() );
        }

        return ptr;
      }
    }
  }
}
