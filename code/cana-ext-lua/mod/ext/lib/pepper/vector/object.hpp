#ifndef __PEPPER_VECTOR_OBJECT_H__
#define __PEPPER_VECTOR_OBJECT_H__

#include <pepper/vector/collection/data.hpp>
#include <pepper/collection.hpp>

#include <pepper/mem.hpp>

#include <vector>

namespace pepper { namespace vector {

  template <typename T> class object : public pepper::collection::object<T>
  {
    protected:
      std::shared_ptr<std::vector<T>> _ptr;

    public:
      object()
      {
        _ptr = mem::shared::make<std::vector<T>>( );
      }

    public:
      object(const std::vector<T> &vec)
      {
        _ptr = mem::shared::make<std::vector<T>>( vec );
      }

    public:
      object(const object<T> &obj)
      {
        _ptr = mem::shared::make<std::vector<T>>(*(obj._ptr));
      }

    public:
      virtual ~object() = default;

    public:
      virtual pepper::collection::data::bean<T> collection(void) const
      {
        return mem::shared::make<pepper::collection::data::object<T>, vector::collection::data::object<T>>(_ptr);
      }

    public:
      std::vector<T> &raw(void)
      {
        return *_ptr;
      }

      const std::vector<T> &raw(void) const
      {
        return *_ptr;
      }

    public:
      std::size_t size(void) const
      {
        return (*_ptr).size();
      }

    public:
      T &at(int off) 
      {
        return (*_ptr)[off];
      }

    public:
      const T &at(int off) const
      {
        return (*_ptr)[off];
      }

    public:
      template <typename Arg> vector::object<T> &emplace(const Arg &arg)
      {
        _ptr->push_back(arg);
        return *this;
      }

    public:
      template <typename Arg> vector::object<T> &emplace(Arg &&arg)
      {
        _ptr->emplace_back(std::move(arg));
        return *this;
      }
  };

} }

#endif
