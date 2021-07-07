#ifndef __PEPPER_OPTPARSE_REQUIRED_H__
#define __PEPPER_OPTPARSE_REQUIRED_H__

#include <pepper/optparse/opt/base.hpp>

#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

namespace pepper { namespace optparse { namespace opt { 
 
  template <typename T> class required : public base 
  {
    public:
      required() = default;
      virtual ~required() = default;

    private:
      boost::optional<T> _value;
    public:
      const T &operator()(void) const 
      {
        return _value.get();
      }

    public:
      virtual bool take(pepper::stream::base<std::string> &s) 
      {
        auto arg = s.lookup(0);
        
        if ( !arg ) {
          return false;
        }

        std::cout << arg.get() << std::endl;

        _value = boost::lexical_cast<T>(arg.get());

        s.forward(1);
        return true;
      }

  };

} } }

#endif
