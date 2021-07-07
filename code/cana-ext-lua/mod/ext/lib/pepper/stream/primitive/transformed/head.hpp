#ifndef __PEPPER_STREAM_PRIMITIVE_TRANSFORMED_HEAD_H__
#define __PEPPER_STREAM_PRIMITIVE_TRASNFORMED_HEAD_H__

#include <pepper/stream/head.hpp>
#include <pepper/fun.hpp>

namespace pepper { namespace stream { namespace primitive { namespace transformed {

  template <typename Arg, typename Ret> class head : public pepper::stream::head::object<Ret>
  {
    private:
      stream::head::bean<Arg> _head;

    public:
      typedef std::function<Ret (const Arg &)> op;
      
    private:
      op _transformer;

    public:
      head(const stream::head::bean<Arg> &head, const op &transformer) : _head{head}, _transformer{transformer}
      {
        // DO NOTHING
      }

      virtual ~head() = default;

    public:
      virtual maybe::object<Ret> access(void) const
      {
        return _head.access().map(_transformer);
      }

    public:
      virtual void forward(void)
      {
        _head.forward();
      }
  };

} } } }

#endif
