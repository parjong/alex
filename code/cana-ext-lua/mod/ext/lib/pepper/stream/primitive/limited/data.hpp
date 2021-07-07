#ifndef __PEPPER_STREAM_LIMITED_DATA_H__
#define __PEPPER_STREAM_LIMITED_DATA_H__

#include <pepper/stream/primitive/limited/head.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace limited {

  template <typename T> class data : public pepper::stream::data::object<T>
  {
    private:
      stream::data::bean<T> _data;
      int _count;

    public:
      data(const stream::data::bean<T> &data, const int &count) : _data{data}, _count{count}
      {
        // DO NOTHING
      }

    public:
      virtual ~data() = default;

    public:
      virtual stream::head::bean<T> head(void) const
      {
        return mem::shared::make<stream::head::object<T>, limited::head<T>>( _data.head(), _count );
      }
  };

} } } }

#endif
