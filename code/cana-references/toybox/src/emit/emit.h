#ifndef EMIT_H__
#define EMIT_H__

#include "hiberlite.h"
#include <vector>

class Emit
{
  public:
    Emit(const std::string& name);
    ~Emit();
  private:
    hiberlite::Database db_;
  public:
    void init(void);
  public:
    template <typename T> std::vector<hiberlite::bean_ptr<T>> enumerate(void)
    {
      return db_.getAllBeans<T>();
    }
  public:
    template <typename T> hiberlite::bean_ptr<T> select(hiberlite::sqlid_t id)
    {
      return db_.loadBean<T>(id);
    }
  public:
    template <typename T> hiberlite::bean_ptr<T> commit(const T& obj)
    {
      return db_.copyBean(obj);
    }
};

#endif
