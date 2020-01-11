#include <pepper/testing.hpp>
#include <pepper/multicast.hpp>

COLLECTION(multicast)
{
  FACT(delegate_usage)
  {
    pepper::multicast::delegate<int, int> d;

    int num_1 = 0;
    int num_2 = 0;

    d += [&] (int n) { return num_1 = n; };
    d += [&] (int n) { return num_2 = n; };

    auto res = d(3);

    EXPECT_EQ( num_1, 3 );
    EXPECT_EQ( num_2, 3 );
    EXPECT_EQ( res.size(), 2 );
  }
}
