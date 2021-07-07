#include <pepper/tokens/scanner.h>

#include <pepper/tokens/cursor.h>

namespace pepper {
  namespace tokens {
    action::base *scanner::find(const std::string &tag) const {
      auto it = tags_.find(tag);
        
      if ( it != tags_.end() ) {
        return it->second;
      }

      for (auto &fun : funs_) {
        if ( fun.first(tag) ) {
          return fun.second;
        }
      }

      return nullptr;
    }
 
    void scanner::add(const std::string &tag, action::base *action) {
      tags_[tag] = action;
    }
   
    void scanner::add(fun_t fun, action::base *action) {
      funs_.emplace_back(fun, action);
    }

    void scanner::scan(stream::base &s) {
      while ( s.lookup(0) ) {
        const char *tok = s.lookup(0).value();
       
        action::base *action = find(tok);

        if ( action == nullptr ) {
          break;
        }

        cursor m(s);

        action->perform(m);
      }
    }

  }
}
