#include "pepper/archive/plain/uint.h"

namespace pepper
{
  bool archive<unsigned int>::read(std::istream& in, unsigned int& num)
  {
    in.read( (char *) &num, sizeof(unsigned int) );  
    return !in.fail();
  }

  bool archive<unsigned int>::write(std::ostream& out, const unsigned int& num)
  {
    out.write( (const char *) &num, sizeof(unsigned int) );
    return !out.fail();
  }
}
