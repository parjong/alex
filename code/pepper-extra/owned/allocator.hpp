#ifndef __PEPPER_OWNED_ALLOCATOR_H__
#define __PEPPER_OWNED_ALLOCATOR_H__

#include <memory>
#include <vector>

namespace pepper { namespace owned {

  template <typename T> class allocator 
  {
    public:
      allocator() = default;
      ~allocator() = default;
    
    private:
      std::vector<std::unique_ptr<T>> _items;

    public:
      template <typename... Args> T &alloc(const Args&... args) 
      {
        T *item = new T{ args... };

        _items.emplace_back(item);

        return *item;
      }
  };

} }

#endif
