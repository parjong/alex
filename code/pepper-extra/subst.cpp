#include "pepper/subst.hpp"
#include "pepper/log.hpp"

#include <vector>

namespace pepper {
  
  pepper::logging::logger subst::__log__{ pepper::log, "subst" };

  std::string subst::rewrite(const std::string &from) const
  {
    static pepper::logging::logger log{ __log__, __func__ };

    std::vector<char> flushed;
    std::vector<char> buffered;

    bool escaped = false;
    bool defered = false;

    for (auto c : from)
    {
      if ( c == '\n' )
      {
        if ( buffered.size() > 0 )            
        {
          flushed.push_back('$');
        }

        flushed.insert(flushed.end(), buffered.begin(), buffered.end());
        buffered.clear();

        flushed.push_back(c);

        escaped = false;
        defered = false;          
      }
      else if ( c == '%' && !escaped )
      {
        escaped = true;                 
      }
      else if ( c == '$' && !escaped )
      {
        if ( defered )
        {
          std::string k{buffered.begin(), buffered.end()};

          log.info( "found a key '%s'", k );

          const std::string &v = _dict.get(k).get();

          flushed.insert(flushed.end(), v.begin(), v.end());
          buffered.clear();

          defered = false;
        }
        else
        {
          defered = true;
        }            
      }
      else
      {
        if ( defered )
        {
          buffered.push_back(c);
        }
        else
        {
          flushed.push_back(c);
        }

        escaped = false;
      }
    }

    return std::string(flushed.begin(), flushed.end());
  }
    
}
