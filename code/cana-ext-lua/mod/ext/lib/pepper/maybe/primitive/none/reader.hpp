#ifndef __PEPPER_MAYBE_PRIMITIVE_NONE_READER_H__
#define __PEPPER_MAYBE_PRIMITIVE_NONE_READER_H__

#include <pepper/maybe/reader.hpp>

namespace pepper { namespace maybe { namespace primitive { namespace none {

  template <typename T> struct reader : public maybe::reader<T>
  {
    public:
      reader() = default;
      virtual ~reader() = default;

    public:
      virtual bool filled(void) const
      {
        return false;
      }

      virtual bool read(const typename maybe::reader<T>::probe &fn) const
      {
        return false;
      }
  };

} } } }

#endif
