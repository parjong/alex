#include <pepper/testing.hpp>
#include <pepper/bucket.hpp>
#include <string>

COLLECTION(bucket)
{
  FACT(insert_and_lookup)
  {
    pepper::bucket::object<int, std::string> bucket;

    bucket.insert(1, "a").insert(1, "b");
    bucket.insert(2, "c");

    EXPECT_EQ(bucket.size(), 2);

    EXPECT_EQ(bucket.lookup(0).count(), 0);
    EXPECT_EQ(bucket.lookup(1).count(), 2);
    EXPECT_EQ(bucket.lookup(2).count(), 1);
  }

  FACT(foreach)
  {
    pepper::bucket::object<int, std::string> bucket;

    bucket.insert(1, "a").insert(1, "b");
    bucket.insert(2, "c");

    std::map<int, std::string> m;

    auto each_fn = [&] (const int &k, const pepper::collection::object<std::string> &ds)
    {
      pepper::collection::foreach(ds) << [&] (const std::string &s)
      {
        m[k] += s;
      };
    };

    bucket.foreach(each_fn);

    EXPECT_EQ(m[1], "ab");
    EXPECT_EQ(m[2], "c");
  }
}
