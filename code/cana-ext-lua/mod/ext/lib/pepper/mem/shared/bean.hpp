#ifndef __PEPPER_MEM_SHARED_BEAN_H__
#define __PEPPER_MEM_SHARED_BEAN_H__

#include <memory>

namespace pepper { namespace mem { namespace shared {

  template <typename T> class bean
  {
    private:
      std::shared_ptr<T> _ptr;

    public:
      bean(const std::shared_ptr<T> &ptr) 
      {
        _ptr = ptr;
      }

    public:
      T &operator()(void) const 
      {
        return *_ptr;
      }
  };

} } }

#endif
