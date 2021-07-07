#ifndef __PEPPER_TOKENS_SCANNER_H__
#define __PEPPER_TOKENS_SCANNER_H__

#include <map>
#include <vector>

#include <pepper/tokens/stream/base.h>
#include <pepper/tokens/action/base.h>

namespace pepper {
  namespace tokens {     
    class scanner {
      public:        
        typedef std::function<bool (const std::string &)> fun_t;

      public:
        scanner() = default;
         ~scanner() = default;
        
      private:
        std::map<std::string, action::base *> tags_;
        std::vector<std::pair<fun_t, action::base *>> funs_;

      public:
        void add(const std::string &token, action::base *);
        void add(fun_t fun, action::base *);

      private:
        action::base *find(const std::string &tag) const;

      public:
        void scan(stream::base &s);
    };
  }
}

#endif
