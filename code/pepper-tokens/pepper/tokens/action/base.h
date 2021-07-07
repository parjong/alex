#ifndef __PEPPER_TOKENS_ACTION_BASE_H__
#define __PEPPER_TOKENS_ACTION_BASE_H__

#include <pepper/tokens/cursor.h>

namespace pepper {
  namespace tokens {
    namespace action {
      class base {
        public:
          base() = default;
          virtual ~base() = default;
        public:
          virtual void perform(cursor &c) = 0;
      };      
    }
  }
}

#endif
