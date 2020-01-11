#ifndef __PEPPER_ATTR_LAZY_READER_H__
#define __PEPPER_ATTR_LAZY_READER__H__

#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace attr { namespace lazy {

  template <typename T> class reader
  {
    public:
      typedef std::function<std::unique_ptr<T> (void)> allocator;

    private:
      allocator _allocator;

    public:
      reader(allocator fn) : _allocator{ fn }
      {
        // DO NOTHING
      }

    private:
      std::unique_ptr<T> _value;

    public:
      const T &operator()(void)
      {
        if ( !_value )
        {
          _value = _allocator();
        }

        return *_value;
      }
  };

} } }

#endif
