#ifndef __PEPPER_MAYBE_PRIMITIVE_MAP_READER_H__
#define __PEPPER_MAYBE_PRIMITIVE_MAP_READER_H__

#include <pepper/maybe/reader.hpp>
#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace maybe { namespace primitive { namespace map {

  template <typename T, typename U> struct reader : public maybe::reader<U>
  {
    private:
      std::shared_ptr<maybe::reader<T>> _ptr;
      std::function<U (const T &)> _map;

    public:
      reader(const std::shared_ptr<maybe::reader<T>> &ptr, const std::function<U (const T &)> &map) : _ptr{ptr}, _map{map}
      {
        // DO NOTHING    
      }

      virtual ~reader() = default;

    public:
      virtual bool filled(void) const
      {
        return _ptr->filled();
      }

      virtual bool read(const typename maybe::reader<U>::probe &fn) const
      {
        auto compose_fn = [&] (const T &value)
        {
          fn(_map(value));
        };
        
        return _ptr->read(compose_fn);
      }
  };

} } } }

#endif
