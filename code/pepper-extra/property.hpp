#ifndef __PEPPER_PROPERTY_H__
#define __PEPPER_PROPERTY_H__

#include "pepper/owned.hpp"

#include <functional>

namespace pepper { namespace property { 

  template <typename T> class rw
  {
    private:
      T _value;
    public:
      rw() = default;
      ~rw() = default;
    public:
      rw(const T &value) : _value{ value }
      {
        // DO NOTHING
      }

    public:
      T &get(void) { return _value; }
      const T &get(void) const { return _value; }

    public:
      T &operator()(void) { return get(); }
      const T &operator()(void) const { return get(); }

    public:
      void set(const T &value) { _value = value; }
  };

  template <typename T> class ro
  {
    private:
      T _value;

    public:
      ro(const T &value) : _value{ value }
      {
        // DO NOTHING
      }
      ~ro() = default;

    public:
      const T &get(void) const { return _value; }
      const T &operator()(void) const { return get(); }
  };

  template <typename T> class ref
  {
    private:
      const T &_value;
    public:
      ref(const T &value) : _value(value)
      {
        // DO NOTHING
      }
      ~ref() = default;
      
    public:
      const T &get(void) const { return _value; }
      const T &operator()(void) const { return get(); }
  };

  template <typename T, typename U> class delayed
  {
    private:
      T &_parent;
      std::function<U *(T &)> _initialize;      

    public:
      delayed(T &parent, std::function<U *(T &)> initialize) 
        : _parent(parent)
        , _initialize(initialize)
      {
        // DO NOTHING
      }
      ~delayed() = default;
    
    private:
      pepper::owned::ptr<U> _ptr;

    public:
      const U &operator()(void)
      {
        if ( _ptr.get() == nullptr )
        {
          _ptr.set( _initialize(_parent) );
        }

        return *( _ptr.get() );
      }
  };


} } 

#endif
