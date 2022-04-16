#ifndef __PEPPER_STREAM_PRIMITIVE_EMPTY_DATA_H__
#define __PEPPER_STREAM_PRIMITIVE_EMPTY_DATA_H__

#include <pepper/stream/primitive/empty/head.hpp>
#include <pepper/stream.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace empty {

  template <typename T> class data : public pepper::stream::data::object<T>
  {
    public:
      data() = default;
      virtual ~data() = default;

    public:
      virtual stream::head::bean<T> head(void) const
      {
        return mem::shared::make<stream::head::object<T>, empty::head<T>>();
      }
  };

} } } }

#endif
