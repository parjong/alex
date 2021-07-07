#ifndef __PEPPER_MAYBE_PRIMITIVE_SOME_READER_H__
#define __PEPPER_MAYBE_PRIMITIVE_SOME_READER_H__

#include <pepper/maybe/reader.hpp>

namespace pepper { namespace maybe { namespace primitive { namespace some {

  template <typename T> struct reader : public maybe::reader<T>
  {
    private:
      const T _value;

    public:
      reader(const T &value) : _value{value}
      {
        // DO NOTHING    
      }

      virtual ~reader() = default;

    public:
      virtual bool filled(void) const
      {
        return true;
      }

      virtual bool read(const typename maybe::reader<T>::probe &fn) const
      {
        fn(_value);
        return true;
      }
  };

} } } }

#endif
