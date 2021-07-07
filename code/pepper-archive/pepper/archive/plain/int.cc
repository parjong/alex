#include "pepper/archive/plain/int.h"

namespace pepper
{
  bool archive<int>::read(std::istream& in, int& num)
  {
    in.read( (char *) &num, sizeof(int) );
    return !in.fail();
  }

  bool archive<int>::write(std::ostream& out, const int& num)
  {
    out.write( (const char *) &num, sizeof(int) );
    return !out.fail();
  }
}
