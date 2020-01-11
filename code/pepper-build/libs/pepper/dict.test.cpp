#include <pepper/testing.hpp>
#include <pepper/dict.hpp>

#include <string>

COLLECTION(dict)
{
  FACT(pod_insert_and_lookup)
  {
    pepper::dict::object<int, std::string> dict;

    dict.insert(0, "a").insert(1, "b");

    EXPECT_TRUE(dict.lookup(0).filled());
    EXPECT_TRUE(dict.lookup(1).filled());
    EXPECT_FALSE(dict.lookup(2).filled());
  }

  FACT(pod_foreach)
  {
    pepper::dict::object<int, int> dict;

    dict.insert(1, 1).insert(2, 2);

    int res = 0;

    auto accum = [&] (int k, int v)
    {
      res += k;
      res += v;
    };

    dict.foreach(accum);

    EXPECT_EQ(res, 6);
  }
}
