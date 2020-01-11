#ifndef __ACTION_MUST_H__
#define __ACTION_MUST_H__

#include "libpepper/factory.hpp"

#include "libscan/cursor.h"

namespace tokens {
  namespace action {
    namespace must {
      struct object { 
        object() = default;
        virtual ~object() = default;

        virtual void perform(cursor &c) = 0;
      };

      struct factory : pepper::factory<object> {
        factory() = default;
        virtual ~factory() = default;
      };
    }
  }
}

#endif
