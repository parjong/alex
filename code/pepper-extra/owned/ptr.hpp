#ifndef __PEPPER_OWNED_PTR_H__
#define __PEPPER_OWNED_PTR_H__

#include <memory>

namespace pepper { namespace owned {

  template <typename T> class ptr : public std::unique_ptr<T>
  {
    public:
      ptr() = default;
      ptr(T *ptr) : std::unique_ptr<T>{ ptr } 
      {
        // DO NOTHING
      }
      virtual ~ptr() = default;

    public:
      void set(T *ptr)
      {
        *(static_cast<std::unique_ptr<T> *>(this)) = std::unique_ptr<T>(ptr);
      }

    public:
      T &operator()(void)
      {
        return *( this->get() );
      }

    public:
      const T &operator()(void) const
      {
        return *( this->get() );
      }
  };

} }

#endif
