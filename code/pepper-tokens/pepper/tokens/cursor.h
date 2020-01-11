#ifndef __PEPPER_TOKENS_CURSOR_H__
#define __PEPPER_TOKENS_CURSOR_H__

#include <pepper/stream/base.h>

namespace pepper 
{
  namespace tokens
  {
    class cursor
    {
      public:
        cursor(stream::base &s);
        ~cursor();

      private:
        stream::base &stream_;

      public:
        void forward(std::size_t off);
        boost::optional<const char *> lookup(std::size_t off) const;

    };
  }
}

#endif
