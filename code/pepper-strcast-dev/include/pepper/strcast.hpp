#ifndef __PEPPER_STRCAST_H__
#define __PEPPER_STRCAST_H__

#include <system_error>

namespace pepper
{

// TODO(parjong) Use string_view
template<typename T> T safe_strcast(const char *, const T &);

template<> int safe_strcast(const char *s, const int &v);

} // namsepace pepper

#endif // __PEPPER_STRCAST_H__
