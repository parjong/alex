#ifndef __PEPPER_COLLECTION_CURSOR_BEAN_H__
#define __PEPPER_COLLECTION_CURSOR_BEAN_H__

#include <pepper/collection/cursor/object.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace collection { namespace cursor {

  template <typename T> class bean
  {
    private:
      std::shared_ptr<cursor::object<T>> _ptr;

    public:
      bean(const std::shared_ptr<cursor::object<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

    public:
      ~bean() = default;

    public:
      cursor::object<T> &object(void) const
      {
        return *_ptr;
      }

    public:
      stream::head::bean<T> head(void) const
      {
        return pepper::stream::head::bean<T>{_ptr};
      }

    public:
      maybe::object<T> access(void) const
      {
        return access(0);
      }

      maybe::object<T> access(unsigned off) const
      {
        return _ptr->access(off);
      }

    public:
      void forward(void)
      {
        forward(1);
      }

      void forward(unsigned off)
      {
        _ptr->forward(off);
      }
  };

} } }

#endif
