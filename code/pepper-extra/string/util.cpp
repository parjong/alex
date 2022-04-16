#include "pepper/string/util.hpp"

#include <functional>

using namespace std::placeholders;

namespace 
{
  template <typename T> class once
  {
    private:
      bool _performed;

      const std::function<T (const T &arg)> _func;      
    public:
      once(std::function<T (const T &arg)> func)
        : _performed{ false }
        , _func{ func }
      {
        // DO NOTHING
      }

    public:
      T operator ()(const T &arg) {
        T res = _performed ? arg : _func(arg);
        _performed = true;
        return res;
      }    
  };

}

namespace pepper { namespace string {

  std::string util::lower(const std::string &from)
  {
    std::string into;
    
    for (const auto &c : from)
    {          
      into += tolower(c);
    }
      
    return into;
  }

  std::string util::upper(const std::string &from)
  {
    std::string into;
    
    for (const auto &c : from)
    {          
      into += toupper(c);
    }
      
    return into;
  }

  std::string util::camel(const std::string &from)
  {
    std::string into;
    
    ::once<char> toupper_fn(std::bind(toupper, _1));

    for (const auto &c : from)
    {          
      into += toupper_fn(c);
    }
      
    return into;
  }

} }

