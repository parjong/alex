#include <pepper/testing.hpp>
#include <pepper/fmt.hpp>

#include <sstream>

COLLECTION(fmt)
{
  FACT(basic)
  {
    std::stringstream ss;

    ss << pepper::fmt::make(3, " + ", 3, " = ", 6);

    EXPECT_EQ( ss.str(), "3 + 3 = 6" );
  }
}
