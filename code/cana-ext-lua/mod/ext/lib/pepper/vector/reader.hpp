#ifndef __PEPPER_VECTOR_READER_H__
#define __PEPPER_VECTOR_READER_H__

#include <pepper/maybe/reader.hpp>
#include <vector>

namespace pepper { namespace vector {

  template <typename T> class reader : public pepper::maybe::reader<T>
  {
    private:
      typename std::vector<T>::const_iterator _cur;

    public:
      reader(const typename std::vector<T>::const_iterator &cur) : _cur{cur}
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
