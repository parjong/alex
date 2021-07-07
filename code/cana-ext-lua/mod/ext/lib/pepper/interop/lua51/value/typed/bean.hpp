#ifndef __PEPPER_INTEROP_LUA51_VALUE_TYPED_BEAN_H__
#define __PEPPER_INTEROP_LUA51_VALUE_TYPED_BEAN_H__

#include <pepper/interop/lua51/value/typed/loader.hpp>

#include <pepper/mem.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace value { namespace typed {

  class bean
  {
    private:
      std::unique_ptr<value::loader> _ptr;

    public:
      template <typename T> bean(const T &value) : _ptr{new typed::loader<T>{value}}
      {
        // DO NOTHING
      }

    public:
      void load(state s) const
      {
        _ptr->load(s);
      }
  };

} } } } }

#endif
