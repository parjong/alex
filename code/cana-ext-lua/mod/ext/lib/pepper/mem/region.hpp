#ifndef __PEPPER_MEM_REGION_H__
#define __PEPPER_MEM_REGION_H__

#include <pepper/mem/factory.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace mem {

  template <typename T> class region
  {
    private:
      std::unique_ptr<T> _ptr;

    public:
      region(const factory<T> &fac) : _ptr{ fac.make() }
      {
        // DO NOTHING
      }

    public:
      ~region() = default;

    public:
      region(region<T> &&r) 
      {
        _ptr = std::move(r._ptr);
      }

    public:
      const region<T> &operator<<(const std::function<void (T &)> &fn) const
      {
        if (_ptr != nullptr)
        {
          fn(*_ptr);
        }

        return *this;
      }
  };

  template <typename T> region<T> use(const mem::factory<T> &fac)
  {
    return region<T>{ fac };
  }

} }

#endif
