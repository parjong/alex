#ifndef __PEPPER_VECTOR_COLLECTION_DATA_OBJECT_H__
#define __PEPPER_VECTOR_COLLECTION_DATA_OBJECT_H__

#include <pepper/vector/cursor.hpp>
#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace vector { namespace collection { namespace data {

  template <typename T> class object : public pepper::collection::data::object<T>
  {
    private:
      std::shared_ptr<std::vector<T>> _ptr;

    public:
      object(const std::shared_ptr<std::vector<T>> &ptr) : _ptr{ptr}
      {
        // DO NOTHING
      }

    public:
      virtual ~object() = default;

   public:
      virtual pepper::collection::cursor::bean<T> cursor(void) const
      {
        return mem::shared::make<pepper::collection::cursor::object<T>, vector::cursor::object<T>>(_ptr);
      }

   public:
      virtual std::unique_ptr<pepper::collection::data::object<T>> clone(void) const
      {
        return mem::unique::make<pepper::collection::data::object<T>, vector::collection::data::object<T>>(*this);
      }
  };

} } } }

#endif
