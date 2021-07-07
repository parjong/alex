#ifndef __PEPPER_ARRAY_CURSOR_OBJECT_H__
#define __PEPPER_ARRAY_CURSOR_OBJECT_H__

#include <pepper/array/reader.hpp>
#include <pepper/collection.hpp>
#include <pepper/mem.hpp>

#include <array>

namespace pepper { namespace array { namespace cursor {

  template <typename T, int N> class object : public pepper::collection::cursor::object<T>
  {
    private:
      std::shared_ptr<std::array<T, N>> _arr;
      typename std::array<T, N>::const_iterator _cur;

    public:
      virtual void forward(unsigned off)
      {
        _cur += off;
      }

    public:
      virtual maybe::object<T> access(unsigned off) const
      {
        auto pos = _cur + off;

        if ( pos >= (*_arr).end() )
        {
          return maybe::none<T>();
        }

        return maybe::make<T, array::reader<T, N>>()(pos);
      }

    public:
      object(const std::shared_ptr<std::array<T, N>> &arr)
      {
        _arr = arr;
        _cur = arr->begin();
      }

    public:
      object(const object& obj) = delete;

    public:
      virtual ~object() = default;
  };

} } }

#endif
