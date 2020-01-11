#ifndef __PEPPER_LINQ_DATASET_H__
#define __PEPPER_LINQ_DATASET_H__

#include <pepper/collection.hpp>
#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace linq {

  template <typename T> class dataset
  {
    private:
      stream::data::bean<T> _data;

    public:
      dataset(const std::shared_ptr<stream::data::object<T>> &ptr) : _data{ptr}
      {
        // DO NOTHING
      }

      dataset(const stream::data::bean<T> &data) : _data{data}
      {
        // DO NOTHING
      }

    public:
      const stream::data::bean<T> &data(void) const
      {
        return *_data;
      }

    public:
      dataset<T> where(const std::function<bool (const T &)> &filter) const
      {
        return dataset<T>{
          mem::shared::make<stream::primitive::filtered::data<T>>(_data, filter)
        };
      }

    public:
      template <typename U> dataset<U> select(const std::function<U (const T &)> &transformer) const
      {
        return dataset<U>{
          mem::shared::make<stream::primitive::transformed::data<T, U>>(_data, transformer)
        };
      }

    public:
      dataset<T> limit(const int &count) const
      {
        return dataset<T>{
          mem::shared::make<stream::primitive::limited::data<T>>(_data, count)
        };
      }

   public:
      template <typename U> U &aggregate(U &acc, const std::function<void (U &, const T &)> &fn) const
      {
        auto apply_fn = [&] (const T &value)
        {
          fn(acc, value);
        };

        for (auto head = _data.head(); head.access().read(apply_fn); head.forward())
        {
          // DO NOTHING
        }

        return acc;
      }

   public:
      int count(void) const
      {
        int res = 0;

        aggregate<int>(res, [] (int &acc, const T &) { ++acc; });

        return res;
      }

   public:
      maybe::object<T> exist(const std::function<bool (const T &)> &pred) const
      {
        auto head = _data.head();

        while (head.access().map(functional::pred::neg(pred)) == true)
        {
          head.forward();
        }

        return head.access();
      }

   public:
      bool forall(const std::function<bool (const T &)> &pred) const
      {
        return !exist(functional::pred::neg(pred)).filled();
      }

   public:
      void foreach(const std::function<void (const T &)> &fn) const
      {
        int res = 0;

        aggregate<int>(res, [&] (int &acc, const T &val) { fn(val); });
      }
  };

  template <typename T> dataset<T> from(const pepper::stream::object<T> &obj)
  {
    return obj.stream();
  }

  template <typename T> dataset<T> from(const pepper::collection::object<T> &obj)
  {
    return obj.collection().stream();
  }

} }

#endif
