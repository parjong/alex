#ifndef __STDEX_SET_H__
#define __STDEX_SET_H__

#include <set>

namespace stdex
{

template <typename T, typename... Args>
std::set<T> make_set(Args&&... args)
{
  return std::set<T>{std::forward<Args>(args)...};
}

} // namespace stdex

template <typename T>
bool operator==(const std::set<T> &lhs, const std::set<T> &rhs)
{
  if (lhs.size() != rhs.size())
  {
    return false;
  }

  for (const auto &e : lhs)
  {
    if (rhs.find(e) == rhs.end())
    {
      return false;
    }
  }

  return true;
}

template <typename T>
std::set<T> operator-(const std::set<T> &lhs, const std::set<T> &rhs)
{
  std::set<T> res;

  for (const auto &e : lhs)
  {
    if (rhs.find(e) == rhs.end())
    {
      res.insert(e);
    }
  }

  return res;
}

#endif // __STDEX_SET_H__
