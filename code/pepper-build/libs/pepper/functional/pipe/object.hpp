#ifndef __PEPPER_FUNCTIONAL_PIPE_OBJECT_H__
#define __PEPPER_FUNCTIONAL_PIPE_OBJECT_H__

#include <functional>

namespace pepper { namespace functional { namespace pipe {

  template <typename T> struct object
  {
    private:
      T _value;

    public:
      operator T &(void)
      {
        return _value;
      }

    public:
      operator const T &(void) const
      {
        return _value;
      }

    public:
      template <typename U> object<U> bind(const std::function<U (const T &)> &f) const
      {
        return pipe::object<U>{ f( _value ) }; 
      }

    public:
      object(const T &value) : _value{ value }
      {
        // DO NOTHING
      }
  };

  template <typename T> pipe::object<T> make(const T &v)
  {
    return pipe::object<T>{v};
  }

} } }

#endif
