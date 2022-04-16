#ifndef __PEPPER_COLLECTION_BLOCK_FORALL_H__
#define __PEPPER_COLLECTION_BLOCK_FORALL_H__

#include <pepper/collection/data.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace collection { namespace block {

  template <typename T> class forall
  {
    public:
      typedef std::function<bool (const T &)> pred;

    private:
      collection::data::bean<T> _data;

    public:
      forall(const collection::data::bean<T> &data) : _data{data}
      {
        // DO NOTHING
      }

    public:
      ~forall() = default;

    public:
      bool operator<<(const pred &p)
      {
        bool res = true;

        auto check = [&] (const T &value)
        {
          res = res && p(value);
        };

				auto it = _data.cursor();

        while (res && it.access().read(check))
        {
					it.forward();
        }

        return res;
      }
  };

} } }

#endif
