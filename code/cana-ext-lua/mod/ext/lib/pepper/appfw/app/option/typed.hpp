#ifndef __PEPPER_APPFW_APP_OPTION_TYPED_H__
#define __PEPPER_APPFW_APP_OPTION_TYPED_H__

#include <pepper/appfw/app/option/desc.hpp>

#include <boost/lexical_cast.hpp>

namespace pepper { namespace appfw { namespace app { namespace option {

  template <typename T> class typed : public desc
  {
    private:
      T _value;

    public:
      typed() = default;
      virtual ~typed() = default;

    private:
      virtual void notify(const std::string &value)
      {
        _value = boost::lexical_cast<T>(value);
      };

    public:
      const T &operator()(void) const 
      {
        return _value;
      }
  };

} } } }

#endif // __PEPPER_APPFW_APP_OPTION_TYPED_H__
