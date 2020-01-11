#ifndef BC_OWNED_H__
#define BC_OWNED_H__

#include <functional>

template <typename T> class owned
{
  public:
    owned(T *ptr, std::function<void (T *)> free) 
      : ptr_(ptr), free_(free) 
    { }
  public:
    ~owned()
    {
      if ( ptr_ != nullptr )
        free_(ptr_);
    }
  private:
    T *ptr_;
    std::function<void (T *)> free_;
  public:
    operator T *(void) const { return ptr_; }
    T *operator->(void) const { return ptr_; }
    T& operator*(void) const { return *ptr_; }
  public:
    T *release(void) 
    { 
      T *ret = ptr_;
      ptr_ = nullptr;
      return ret;
    }
};


#endif
