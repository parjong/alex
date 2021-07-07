#ifndef __PEPPER_ARRAY_STREAM_DATA_OBJECT_H__
#define __PEPPER_ARRAY_STREAM_DATA_OBJECT_H__

#include <pepper/array/cursor.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>

#include <array>

namespace pepper { namespace array { namespace stream { namespace data {

  template <typename T, int N> class object : public pepper::stream::data::object<T>
  {
    private:
      std::shared_ptr<std::array<T, N>> _arr;

    public:
      object(const std::shared_ptr<std::array<T, N>> &arr)
      {
        _arr = arr;
      }

    public:
      virtual ~object() = default;

    public:
      virtual pepper::stream::head::bean<T> head(void) const
      {
        return mem::shared::make<pepper::stream::head::object<T>, array::cursor::object<T, N>>( _arr );
      }
  };

} } } }

#endif
