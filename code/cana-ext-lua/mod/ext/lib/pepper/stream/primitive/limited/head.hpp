#ifndef __PEPPER_STREAM_PRIMITIVE_LIMITED_HEAD_H__
#define __PEPPER_STREAM_PRIMITIVE_LIMITED_HEAD_H__

#include <pepper/stream/head.hpp>
#include <pepper/mem.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace limited {

  template <typename T> class head : public pepper::stream::head::object<T>
  {
    private:
      stream::head::bean<T> _head;
      int _count;

    public:
      head(const stream::head::bean<T> &head, const int count) : _head{head}, _count{std::max(count, 0)}
      {
        // DO NOTHING
      }

    public:
      virtual ~head() = default;

    public:
      virtual maybe::object<T> access(void) const
      {
        if ( _count > 0 )
        {
          return _head.access();
        }

        return maybe::none<T>();
      }

    public:
      virtual void forward(void)
      {
        _head.forward();
        _count = std::max( _count - 1, 0 );
      }
  };

} } } }

#endif
