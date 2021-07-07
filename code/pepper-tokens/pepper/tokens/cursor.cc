#include <pepper/tokens/cursor.h>

namespace pepper
{
  namespace tokens
  {
    cursor::cursor(stream::base &stream) 
      : stream_(stream)
    {
      // DO NOTHING
    }

    cursor::~cursor()
    {
      // DO NOTHING
    }

    void cursor::forward(std::size_t off) 
    {
      stream_.forward(off);
    }

    boost::optional<const char *> cursor::lookup(std::size_t off) const 
    {
      return stream_.lookup(off);
    }

  }
}

