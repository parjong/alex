#ifndef __PEPPER_STRCAST_H__
#define __PEPPER_STRCAST_H__

namespace pepper
{

/**
 * @brief Convert a C string value as a value of T type
 *
 * safe_strcast(s, v) returns v if s is null.
 * safe_strcast(s, v) returns a value of T type that corresponds to "s" if "s" is convertible.
 *
 * TODO(parjong) Define the behavior when "s" is inconvertible.
 */
template<typename T> T safe_strcast(const char *, const T &);

template<> int safe_strcast(const char *s, const int &v);

} // namsepace pepper

#endif // __PEPPER_STRCAST_H__
