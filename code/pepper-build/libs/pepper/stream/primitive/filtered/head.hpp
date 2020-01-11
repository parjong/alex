#ifndef __PEPPER_STREAM_PRIMITIVE_FILTERED_HEAD_H__
#define __PEPPER_STREAM_PRIMITIVE_FILTERED_HEAD_H__

#include <pepper/stream/head.hpp>
#include <pepper/functional.hpp>
#include <pepper/mem.hpp>

namespace pepper { namespace stream { namespace primitive { namespace filtered {

  template <typename T> class head : public pepper::stream::head::object<T>
  {
    private:
      stream::head::bean<T> _head;
      std::function<bool (const T &)> _filter;

    public:
      head(const stream::head::bean<T> &head, const std::function<bool (const T &)> &filter) : _head{head}, _filter{filter}
      {
        next();
      }

    public:
      virtual ~head() = default;

    private:
      void next(void) 
      {
        while ( _head.access().filled() )
        {
          if (_head.access().map(_filter) == true)
          {
            break;
          }

          _head.forward();
        }
      }

    public:
      virtual maybe::object<T> access(void) const
      {
        return _head.access();
      }

    public:
      virtual void forward(void)
      {
        _head.forward(); next();
      }
  };

} } } }

#endif
