#ifndef __PEPPER_VECTOR_STREAM_DATA_OBJECT_H__
#define __PEPPER_VECTOR_STREAM_DATA_OBJECT_H__

#include <pepper/vector/cursor.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace vector { namespace stream { namespace data {

  template <typename T> class object : public pepper::stream::data::object<T>
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
      virtual pepper::stream::head::bean<T> head(void) const
      {
        return mem::shared::make<pepper::stream::head::object<T>, vector::cursor::object<T>>(_ptr);
      }
  };

} } } }

#endif
