#ifndef __PEPPER_COLLECTION_PRIMITIVE_FOREACH_H__
#define __PEPPER_COLLECTION_PRIMITIVE_FOREACH_H__

#include <pepper/collection/data.hpp>
#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace collection { namespace primitive {

  template <typename T> class foreach
  {
    public:
      typedef std::function<void (const T &)> func;

    private:
      collection::data::bean<T> _data;

    public:
      foreach(const collection::data::bean<T> &data) : _data{data}
      {
        // DO NOTHING
      }

      ~foreach() = default;

    public:
      void operator<<(const func &fn)
      {
				auto it = _data.cursor();

        while (it.access().read(fn))
        {
					it.forward();
        }
      }
  };

} } }

#endif
