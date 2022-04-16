#ifndef __PLUGIN_CONSUMER_H__
#define __PLUGIN_CONSUMER_H__

#include <string>
#include <vector>

#include "libpepper/factory.hpp"

namespace tokens {
  namespace plugin {
    namespace consumer {
      struct object {
        object() = default;
        virtual ~object() = default;

        virtual void consume(const std::vector<std::string>& args) = 0;
      };

      struct factory : public pepper::factory<object> {
        factory() = default;
        virtual ~factory() = default;
      };
    }
  }
}

#endif
