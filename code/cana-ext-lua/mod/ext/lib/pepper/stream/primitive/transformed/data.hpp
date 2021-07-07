#ifndef __PEPPER_STREAM_TRANSFORMED_DATA_H__
#define __PEPPER_STREAM_TRANSFORMED_DATA_H__

#include <pepper/stream/primitive/transformed/head.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace transformed {

  template <typename Arg, typename Ret> class data : public pepper::stream::data::object<Ret>
  {
    private:
      stream::data::bean<Arg> _data;
 
    public:
      typedef std::function<Ret (const Arg &)> op;
    private:
      op _transformer;

    public:
      data(const stream::data::bean<Arg> &data, const op &transformer) : _data{data}, _transformer{transformer}
      {
        // DO NOTHING
      }

    public:
      virtual ~data() = default;

    public:
      virtual stream::head::bean<Ret> head(void) const
      {
        return mem::shared::make<stream::head::object<Ret>, transformed::head<Arg, Ret>>( _data.head(), _transformer );
      }
  };

} } } }

#endif
