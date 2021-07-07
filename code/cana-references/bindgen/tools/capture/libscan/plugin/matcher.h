#ifndef __PLUGIN_MATCHER_H__
#define __PLUGIN_MATCHER_H__

#include <boost/regex.hpp>

#include "libpepper/factory.hpp"

namespace tokens {
  namespace plugin {
    namespace matcher {
      struct object {
        object() = default;
        virtual ~object() = default;

        virtual void match(const boost::smatch &sm) = 0;
      };

      struct factory : public pepper::factory<object> {
        factory() = default;
        virtual ~factory() = default;
      };
    }
  }
}


#endif
