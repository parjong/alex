#ifndef __PEPPER_ARRAY_READER_H__
#define __PEPPER_ARRAY_READER_H__

#include <pepper/maybe/reader.hpp>

#include <array>

namespace pepper { namespace array {

  template <typename T, int N> class reader : public pepper::maybe::reader<T>
  {
    private:
      typename std::array<T, N>::const_iterator _cur;

    public:
      reader(const typename std::array<T, N>::const_iterator &cur) : _cur{cur}
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
        fn(*_cur);
        return true;
      }
  };

} }

#endif
