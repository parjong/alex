#ifndef __ACTION_MAY_H__
#define __ACTION_MAY_H__

#include "libpepper/factory.hpp"
#include "libscan/cursor.h"

namespace tokens {
  namespace action {
    namespace may {
      struct object {
        object() = default;
        virtual ~object() = default;

        virtual bool perform(cursor &c) = 0;
      };
    
      struct factory : pepper::factory<object> {
        factory() = default;
        virtual ~factory() = default;
      };
    }
  }
}

#endif
