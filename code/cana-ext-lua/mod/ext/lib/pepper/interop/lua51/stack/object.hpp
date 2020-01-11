#ifndef __PEPPER_INTEROP_LUA51_STACK_OBJECT_H__
#define __PEPPER_INTEROP_LUA51_STACK_OBJECT_H__

#include <pepper/interop/lua51/state.hpp>
#include <pepper/interop/lua51/stack/accessor.hpp>

namespace pepper { namespace interop { namespace lua51 { namespace stack {

  class object
  {
    private:
      state _state;

    public:
      object(state s);

    public:
      int size(void) const;

      template <typename T> void push(const T &value)
      {
        accessor<T>::push(_state, value);
      };

      template <typename T> T pop(void)
      {
        return accessor<T>::pop(_state);
      }
  };

} } } }

#endif
