#ifndef __PEPPER_MAYBE_OBJECT_H__
#define __PEPPER_MAYBE_OBJECT_H__

#include <pepper/maybe/reader.hpp>
#include <pepper/maybe/primitive/map/reader.hpp>
#include <pepper/maybe/primitive/some/reader.hpp>
#include <pepper/maybe/primitive/none/reader.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace maybe {

  template <typename T> class object
  {
    private:
      std::shared_ptr<maybe::reader<T>> _ptr;

    public:
      object(const std::shared_ptr<maybe::reader<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

      ~object() = default;

    public:
      bool filled(void) const
      {
        return _ptr->filled();
      }

    public:
      bool read(const typename maybe::reader<T>::probe &fn) const
      {
        return _ptr->read(fn);
      }

    public:
      template <typename U> object<U> map(const std::function<U (const T &)> &fn) const
      {
        return pepper::mem::shared::make<pepper::maybe::reader<U>, pepper::maybe::primitive::map::reader<T, U>>(_ptr, fn);
      }
  };

  template <typename T, typename R> struct factory
  {
    factory() = default;
    ~factory() = default;

    template <typename... Args> object<T> operator()(Args... args) const
    {
      return pepper::mem::shared::make<pepper::maybe::reader<T>, R>(args...);
    }
  };

  template <typename T, typename R> const factory<T, R> &make(void)
  {
    static factory<T, R> f;
    return f;
  }

  template <typename T> object<T> none(void)
  {
    return make<T, pepper::maybe::primitive::none::reader<T>>()();
  }

  template <typename T> object<T> some(const T &value)
  {
    return make<T, pepper::maybe::primitive::some::reader<T>>()(value);
  }

  template <typename T> bool operator==(const object<T> &lhs, const T &rhs)
  {
    bool ret = false;

    auto compare = [&ret, &rhs] (const T &value)
    {
      if (value == rhs)
      {
        ret = true;
      }
    };

    lhs.read(compare);

    return ret;
  }

  template <typename T> bool operator!=(const object<T> &lhs, const T &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T> bool operator==(const T &lhs, const object<T> &rhs)
  {
    return rhs == lhs;
  }

  template <typename T> bool operator!=(const T &lhs, const object<T> &rhs)
  {
    return rhs != lhs;
  }

} }

#endif
