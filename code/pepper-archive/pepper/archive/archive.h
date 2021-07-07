#ifndef PEPPER_ARCHIVE_H__
#define PEPPER_ARCHIVE_H__

#include <iostream>

namespace pepper
{
  template <typename T> struct archive
  {
    static bool read(std::istream&, T&);
    static bool write(std::ostream&, const T&);
  };
}

#endif
