#ifndef __PEPPER_STREAM_PRIMITIVE_EMPTY_HEAD_H__
#define __PEPPER_STREAM_PRIMITIVE_EMPTY_HEAD_H__

#include <pepper/stream/head.hpp>

namespace pepper { namespace stream { namespace primitive { namespace empty {

  template <typename T> class head : public pepper::stream::head::object<T>
  {
    public:
      head() = default;
      virtual ~head() = default;

    public:
      virtual maybe::object<T> access(void) const
      {
        return maybe::none<T>();
      }

    public:
      virtual void forward(void)
      {
        // DO NOTHING
      }
  };

} } } }

#endif
