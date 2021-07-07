#ifndef __PEPPER_INTEROP_LUA51_VALUE_TYPED_LOADER_H__
#define __PEPPER_INTEROP_LUA51_VALUE_TYPED_LOADER_H__

#include <pepper/interop/lua51/value/loader.hpp>
#include <pepper/interop/lua51/stack/accessor.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace value { namespace typed {

  template <typename T> class loader : public value::loader
  {
    private:
      T _value;

    public:
      loader(const T &value) : _value{value}
      {
        // DO NOTHING
      }

      virtual ~loader() = default;

    public:
      virtual void load(state s) const
      {
        stack::accessor<T>::push(s, _value);
      }
  };

} } } } }

#endif
