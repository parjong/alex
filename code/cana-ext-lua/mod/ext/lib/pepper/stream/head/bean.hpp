#ifndef __PEPPER_STREAM_HEAD_BEAN_H__
#define __PEPPER_STREAM_HEAD_BEAN_H__

#include <pepper/stream/head/object.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace stream { namespace head {

  template <typename T> class bean
  {
    private:
      std::shared_ptr<head::object<T>> _ptr;

    public:
      bean(const std::shared_ptr<head::object<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

    public:
      bean(const bean &b) : _ptr{b._ptr}
      {
        // DO NOTHING
      }

    public:
      ~bean() = default;

    public:
      void forward(void)
      {
        _ptr->forward();
      }

      pepper::maybe::object<T> access(void) const
      {
        return _ptr->access();
      }
  };

} } }

#endif
