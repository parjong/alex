#ifndef __PEPPER_OPT_H__
#define __PEPPER_OPT_H__

#include <boost/optional.hpp>

namespace pepper {

  template <typename T> class opt
  {
    private:
      boost::optional<T> _value;

    public:
      opt() = default;
      opt(const T &value) : _value{ value }
      {

      }
      ~opt() = default;

    public:
      bool is_initialized(void) const
      {
        return (bool) _value; 
      }

      const T &get(void) const 
      { 
        return *_value; 
      }

      void set(const T &value)
      {
        _value = value;
      }

      void map(std::function<void (const T &)> fn) const
      {
        if ( is_initialized() )
          fn( get() );
      }

      const T &operator()(void) const { return get(); }

      opt &operator=(const T &value)
      {
        this->set(value);
        return *this;
      }
  };

} 

#endif
