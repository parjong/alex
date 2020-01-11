#ifndef __PEPPER_OPTIONAL_OBJECT_H__
#define __PEPPER_OPTIONAL_OBJECT_H__

#include <pepper/functional.hpp>
#include <pepper/maybe.hpp>
#include <pepper/mem.hpp>

#include <boost/optional.hpp>

namespace pepper { namespace optional {

  template <typename T> class object
  {
    private:
      boost::optional<T> _value;

    public:
      object()
      {
        // DO NOTHING
      }

      object(const T &value) : _value{value}
      {
        // DO NOTING
      }

      object(const maybe::object<T> &b)
      {
        auto set = [&] (const T &value)
        {
          _value = value;
        };

        b.read(set);
      }

    public:
      ~object() = default;

    public:
      bool filled(void) const
      {
        return (bool) _value;
      }

      bool read(const typename maybe::reader<T>::probe &fn) const
      {
        if ( !filled() )
        {
          return false;
        }

        fn( *_value );
        return true;
      }

    public:
      template <typename U> U join(const std::function<U (const T &)> &tf, const std::function<U (void)> &ff) const
      {
        if ( !filled() )
        {
          return ff();
        }

        return tf( *_value );
      }

    public:
      T get(const std::function<T ()> &ff) const
      {
        auto tf = [] (const T &value)
        {
          return value;
        };

        return join<T>(tf, ff);
      }

    public:
      T get(const T &v) const
      {
        return get([&] (void) { return v; });
      }

    public:
      optional::object<T> &set(const T &value)
      {
        _value = value;
        return *this;
      }

    public:
      optional::object<T> &replace(const std::function<T (const T &)> &fn)
      {
        if ( filled() )
        {
          _value = fn(*_value);
        }

        return *this;
      }

    public:
      optional::object<T> &rewrite(const std::function<void (T &)> &fn)
      {
        if ( filled() )
        {
          fn( *_value );
        }

        return *this;
      }

    public:
      template <typename U> optional::object<U> map(const std::function<optional::object<U> (const T &)> &fn) const
      {
        if ( !filled() )
        {
          return optional::object<U>{ };
        }

        return fn(*_value);
      }

      template <typename U> optional::object<U> map(const std::function<U (const T &)> &fn) const
      {
        auto wrapped_fn = [&] (const T &v)
        {
          return optional::object<U>{ fn(v) };
        };

        return map<U>(wrapped_fn);
      }

    public:
      optional::object<T> &operator=(const T &value)
      {
        return set(value);
      }
  };

  template <typename T> optional::object<T> none(void)
  {
    return optional::object<T>{ };
  }


  template <typename T> optional::object<T> some(const T &v)
  {
    return optional::object<T>{ v };
  }


} }

#endif
