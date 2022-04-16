#ifndef PEPPER_ARCHIVE_UTIL_H__
#define PEPPER_ARCHIVE_UTIL_H__

#include "pepper/archive/archive.h"

namespace pepper
{
  struct archiveutil
  {
    template <typename T> static bool readfrom(IStream& is, T& obj) 
    { 
      return Archive<T>::ReadFrom(is, obj); 
    }

    template <typename T> static bool writeto(OStream& os, const T& obj) 
    {
      return Archive<T>::WriteTo(os, obj);
    }
  };

}

#endif
