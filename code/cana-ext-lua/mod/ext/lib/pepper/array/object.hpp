#ifndef __PEPPER_ARRAY_OBJECT_H__
#define __PEPPER_ARRAY_OBJECT_H__

#include <pepper/array/collection/data.hpp>
#include <pepper/collection.hpp>

#include <pepper/mem.hpp>

#include <array>

namespace pepper { namespace array {

  template <typename T, int N> class object : public pepper::collection::object<T>
  {
    private:
      std::shared_ptr<std::array<T, N>> _ptr;

    public:
      object() 
      {
        _ptr = mem::shared::make<std::array<T, N>>(); 
      }

    public:
      object(const object &obj)
      {
        _ptr = mem::shared::make<std::array<T, N>>( obj.raw() );
      }

    public:
      virtual ~object() = default;

    public:
      virtual pepper::collection::data::bean<T> collection(void) const
      {
        return mem::shared::make<pepper::collection::data::object<T>, array::collection::data::object<T, N>>(_ptr);
      }

    public:
      std::array<T, N> &raw(void)
      {
        return *_ptr;
      }

      const std::array<T, N> &raw(void) const
      {
        return *_ptr;
      }
  };

} }

#endif
