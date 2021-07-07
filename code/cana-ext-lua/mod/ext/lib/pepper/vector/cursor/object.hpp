#ifndef __PEPPER_VECTOR_CURSOR_OBJECT_H__
#define __PEPPER_VECTOR_CURSOR_OBJECT_H__

#include <pepper/vector/reader.hpp>
#include <pepper/collection.hpp>
#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace vector { namespace cursor {

  template <typename T> class object : public pepper::collection::cursor::object<T>
  {
    private:
      typename std::shared_ptr<std::vector<T>> _vec;
      typename std::vector<T>::const_iterator _cur;

    public:
      virtual ~object() = default;

    public:
      virtual void forward(unsigned off)
      {
        _cur += off;
      }

    public:
      virtual maybe::object<T> access(unsigned off) const
      {
        if ( _cur + off >= (*_vec).end() )
        {
          return maybe::none<T>();
        }

        return maybe::make<T, vector::reader<T>>()(_cur + off);
      }

    public:
      object(const std::shared_ptr<std::vector<T>> &vec)
      {
        _vec = vec;
        _cur = vec->begin();
      }
  };

} } }

#endif
