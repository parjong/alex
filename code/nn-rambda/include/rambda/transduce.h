#ifndef __RAMBDA_TRANSDUCE_H__
#define __RAMBDA_TRANSDUCE_H__

#include <functional>

namespace rambda
{

template<typename T>
using Pred = std::function<bool (const T&)>;

template<typename T>
using CSink = std::function<void (const T&)>;

template<typename T>
using Sink = std::function<void (T&&)>;

namespace sink
{
template<typename T>
CSink<T> seq(const CSink<T> &sink)
{
  return sink;
}

template<typename T>
CSink<T> seq(const CSink<T> &fst, const CSink<T> &snd)
{
  return [fst, snd] (const T &value)
  {
    fst(value);
    snd(value);
  };
}

#if __cplusplus >= 201402L
template<typename T, typename... Args>
auto seq(const CSink<T> &fst, const CSink<T> &snd, Args&&... args)
{
  return seq(fst, seq(snd, std::forward<Args>(args)...));
}
#endif
} // namespace sink

template<typename T, typename U>
using Transform = std::function<Sink<T> (const Sink<U> &)>;

namespace xform
{

template<typename T>
Transform<T, T> unit(void)
{
  return [] (const Sink<T> &sink)
  {
    return sink;
  };
}

template<typename T, typename U>
Transform<T, U> map(const std::function<U (const T &)> &f)
{
  return [f] (const Sink<U> &sink)
  {
    return [f, sink] (T&& value)
    {
      return sink(f(std::move(value)));
    };
  };
}

template<typename T>
Transform<T, T> filter(const Pred<T> &p)
{
  return [p] (const Sink<T> &sink)
  {
    return [p, sink] (T&& value)
    {
      if (p(value))
      {
        sink(std::move(value));
      }
    };
  };
}

template<typename T, typename U>
Transform<T, U> compose(const Transform<T, U> &xform)
{
  return xform;
}

template<typename T, typename U, typename V>
Transform<T, V> compose(const Transform<T, U> &fst, const Transform<U, V> &snd)
{
  return [fst, snd] (const Sink<V> &sink)
  {
    return fst(snd(sink));
  };
}

#if __cplusplus >= 201402L
template<typename T, typename U, typename V, typename... Args>
Transform<T, V> compose(const Transform<T, U> &fst, const Transform<U, V> &snd, Args&&... args)
{
  return compose(fst, compose(snd, std::forward<Args>(args)...));
}
#endif

} // namespace xform

template<typename It, typename T>
void transduce(It beg, It end, const Sink<T> &sink)
{
  for (auto it = beg; it != end; ++it)
  {
    auto v = *it;
    sink(std::move(v));
  }
}

template<typename It, typename T, typename U>
void transduce(It beg, It end, const Transform<T, U> &xform, const Sink<U> &sink)
{
  transduce(beg, end, xform(sink));
}

template<typename Collection, typename T, typename U>
void transduce(const Collection &c, const Transform<T, U> &xform, const Sink<U> &sink)
{
  transduce(std::cbegin(c), std::cend(c), xform, sink);
}

} // namespace rambda

#endif // __RAMBDA_TRANSDUCE_H__
