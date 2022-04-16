#ifndef PEPPER_ARCHIVE_INT_H__
#define PEPPER_ARCHIVE_INT_H__

#include "pepper/archive/archive.h"

namespace pepper
{
  template <> struct archive<int>
  {
    static bool read(std::istream&, int&);
    static bool write(std::ostream&, const int&);
  };
}

#endif
