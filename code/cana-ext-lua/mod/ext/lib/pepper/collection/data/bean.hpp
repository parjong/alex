#ifndef __PEPPER_COLLECTION_DATA_BEAN_H__
#define __PEPPER_COLLECTION_DATA_BEAN_H__

#include <pepper/collection/data/object.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace collection { namespace data {

  template <typename T> class bean
  {
    private:
      std::shared_ptr<data::object<T>> _ptr;

    public:
      bean(const std::shared_ptr<data::object<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

    public:
      ~bean() = default;

    public:
      stream::data::bean<T> stream(void) const
      {
        return stream::data::bean<T>{_ptr};
      }

    public:
      collection::cursor::bean<T> cursor(void) const
      {
        return _ptr->cursor();
      }
  };

} } }

#endif
