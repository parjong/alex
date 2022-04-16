#ifndef __PEPPER_STREAM_DATA_BEAN_H__
#define __PEPPER_STREAM_DATA_BEAN_H__

#include <pepper/stream/data/object.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace stream { namespace data {

  template <typename T> class bean
  {
    private:
      std::shared_ptr<data::object<T>> _ptr;

    public:
      bean(const bean &b) : _ptr{b._ptr}
      {
        // DO NOTHING
      }

    public:
      bean(const std::shared_ptr<data::object<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

    public:
      ~bean() = default;

    public:
      stream::head::bean<T> head(void) const
      {
        return _ptr->head();
      }
  };

} } }

#endif
