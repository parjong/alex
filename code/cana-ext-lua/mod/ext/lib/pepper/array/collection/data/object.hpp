#ifndef __PEPPER_ARRAY_COLLECTION_DATA_OBJECT_H__
#define __PEPPER_ARRAY_COLLECTION_DATA_OBJECT_H__

#include <pepper/array/cursor.hpp>
#include <pepper/collection.hpp>
#include <pepper/mem.hpp>

#include <array>

namespace pepper { namespace array { namespace collection { namespace data {

  template <typename T, int N> class object : public pepper::collection::data::object<T>
  {
    private:
      std::shared_ptr<std::array<T, N>> _arr;

    public:
      object(const std::shared_ptr<std::array<T, N>> &arr) : _arr{arr}
      {
        // DO NOTHING
      }

    public:
      virtual ~object() = default;

    public:
      virtual pepper::collection::cursor::bean<T> cursor(void) const
      {
        return mem::shared::make<pepper::collection::cursor::object<T>, array::cursor::object<T, N>>(_arr);
      }
  };

} } } }

#endif
