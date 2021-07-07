#ifndef __RAMBDA_COMPOSE_H__
#define __RAMBDA_COMPOSE_H__

#include <functional>

namespace rambda
{

template<typename T, typename U>
using Fn = std::function<U (T)>;

template<typename T, typename U>
Fn<T, U> compose(const Fn<T, U> &f)
{
  return f;
}

template<typename T, typename U, typename V>
Fn<T, V> compose(const Fn<T, U> &f, const Fn<U, V> &g)
{
  return [f, g] (U value)
  {
    return g(f(value));
  };
}

#if __cplusplus >= 201402L
template<typename T, typename U, typename V, typename... Args>
auto compose(const Fn<T, U> &f, const Fn<U, V> &g, Args&&... args)
{
  return compose(f, compose(g, std::forward<Args>(args)...));
}
#endif

} // namespace rambda

#endif // __RAMBDA_COMPOSE_H__
