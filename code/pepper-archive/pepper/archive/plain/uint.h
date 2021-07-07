#ifndef PEPPER_ARCHIVE_U_INT_H__
#define PEPPER_ARCHIVE_U_INT_H__

#include "pepper/archive/archive.h"

namespace pepper
{
  template <> struct archive<unsigned int>
  {
    static bool read(std::istream&, unsigned int&);
    static bool write(std::ostream&, const unsigned int&);
  };
}

#endif
