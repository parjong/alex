#ifndef CORE_ARCHIVE_VECTOR_H__
#define CORE_ARCHIVE_VECTOR_H__

#include "pepper/archive/archive.h"

#include <vector>

namespace pepper
{
  template <typename T> struct archive<std::vector<T>>
  {
    static bool read(std::istream& in, std::vector<T>& vec)
    {
      vec.clear();

      int len = 0;

      if ( !archive<int>::read(in, len) ) return false;

      for (int i = 0; i < len; ++i)
      {
        T elem;

        if ( !archive<T>::read(in, elem) ) return false;

        vec.push_back(elem);
      }
      
      return true;
    }

    static bool write(std::ostream& out, const std::vector<T>& vec)
    {
      const int len = vec.size();

      if ( !archive<int>::write(out, len) ) return false;

      for ( const T& elem : vec )
      {
        if ( !archive<T>::write(out, elem) ) return false;      
      }

      return true;
    }
  };
}

#endif
