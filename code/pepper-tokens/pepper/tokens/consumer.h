#ifndef __PEPPER_TOKENS_CONSUMER_H__
#define __PEPPER_TOKENS_CONSUMER_H__

#include <array>

namespace pepper {
  namespace tokens {
    template <unsigned int N> class consumer {
      public:
        consumer() = default;
        virtual ~consumer() = default;

      public:
        virtual void consume(const std::array<const char *, N> &args) = 0;
    };
  }
}

#endif
