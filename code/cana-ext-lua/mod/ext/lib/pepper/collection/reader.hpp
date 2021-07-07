#ifndef __PEPPER_COLLECTION_READER_H__
#define __PEPPER_COLLECTION_READER_H__

#include <pepper/optional.hpp>

namespace pepper { namespace collection {

  template <typename T> class reader 
  {
    public:
      reader() = default;
      virtual ~reader() = default;

    public:
      virtual maybe::object<T> access(unsigned off) const = 0;
  };

} }

#endif
