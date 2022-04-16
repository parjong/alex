#ifndef __PEPPER_TOKENS_ACTION_CONSUME_H__
#define __PEPPER_TOKENS_ACTION_CONSUME_H__

#include <pepper/tokens/consumer.h>

#include <pepper/tokens/action/base.h>

namespace pepper {
  namespace tokens {
    namespace action {
      template <unsigned int N> class consume : public base {
        public:
          consume() = default;
          virtual ~consume() = default;

        public:
          virtual void perform(cursor &c) {
            std::array<const char *, N> arr;

            for (int i = 0; i < N; ++i) {
              boost::optional<const char *> elem = c.lookup(0);

              if ( !elem ) {
                return;
              }

              arr[i] = elem.value();

              c.forward(1);
            }  

            for (consumer<N> *p : consumers_) {
              p->consume(arr);
            }
          }

        private:
          std::vector<consumer<N> *> consumers_;
        public:
          void add(consumer<N> &p) {
            consumers_.push_back(&p);
          }
      };     
    }
  }
}

#endif
