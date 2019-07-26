#ifndef __PEPPER_STR_H__
#define __PEPPER_STR_H__

#include <ostream>
#include <sstream>
#include <string>

namespace pepper
{

template <typename... Args> void _str(std::ostream &os, Args&&... args);

template <> void _str(std::ostream &os) { return; }
template <typename Arg> void _str(std::ostream &os, Arg&& arg) { os << arg; }
template <typename Arg, typename... Args> void _str(std::ostream &os, Arg&& arg, Args&&... args)
{
  _str(os, std::forward<Arg>(arg));
  _str(os, std::forward<Args>(args)...);
}

template <typename... Args> std::string str(Args&&... args)
{
  std::stringstream ss;
  _str(ss, std::forward<Args>(args)...);
  return ss.str();
}

} // namsepace pepper

#endif // __PEPPER_STR_H__
