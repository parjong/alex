#ifndef __FIPE_H__
#define __FIPE_H__

#include <functional>
#include <utility>

namespace fipe
{

// Wrap a function pointer as a callable std::function
template <typename Ret, typename Args>
std::function<Ret (Args)> wrap(Ret (*p)(Args))
{
  return p;
}

} // namespace fipe

template <typename T, typename Callable>
auto operator|(T &&v, Callable &&f) -> decltype(f(v))
{
  return std::forward<Callable>(f)(v);
}

#endif // __FIPE_H__
