#include <pepper/testing.hpp>
#include <pepper/delegate.hpp>

COLLECTION(delegate)
{
  FACT(unicast_object_usage)
  {
    pepper::delegate::unicast::object<int, int> d;

    int num_1 = 0;
    int num_2 = 0;

    d = [&] (int n) { return num_1 = n; };

    int ret_1 = d(3);

    EXPECT_EQ(ret_1, 3);
    EXPECT_EQ(num_1, 3);
    EXPECT_EQ(num_2, 0);

    d = [&] (int n) { return num_2 = n; };

    int ret_2 = d(4);

    EXPECT_EQ(ret_2, 4);
    EXPECT_EQ(num_1, 3);
    EXPECT_EQ(num_2, 4);
  }

  FACT(multicast_object_usage)
  {
    pepper::delegate::multicast::object<int, int> d;

    int num_1 = 0;
    int num_2 = 0;

    d += [&] (int n) { return num_1 = n; };
    d += [&] (int n) { return num_2 = n; };

    auto res = d(3);

    EXPECT_EQ(num_1, 3);
    EXPECT_EQ(num_2, 3);
    EXPECT_EQ(res.size(), 2);
  }
}
