#ifndef __PEPPER_STREAM_PRIMITIVE_FILTERED_DATA_H__
#define __PEPPER_STREAM_PRIMITIVE_FILTERED_DATA_H__

#include <pepper/stream/primitive/filtered/head.hpp>
#include <pepper/stream/data.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace filtered {

  template <typename T> class data : public pepper::stream::data::object<T>
  {
    private:
      stream::data::bean<T> _data;
      std::function<bool (const T &)> _filter;

    public:
      data(const stream::data::bean<T> &data, const std::function<bool (const T &)> &filter) : _data{data}, _filter{filter}
      {
        // DO NOTHING
      }

    public:
      virtual ~data() = default;

    public:
      virtual stream::head::bean<T> head(void) const
      {
        return mem::shared::make<stream::head::object<T>, filtered::head<T>>( _data.head(), _filter );
      }
  };

} } } }

#endif
