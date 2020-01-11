#include <pepper/testing.hpp>
#include <pepper/collection.hpp>

COLLECTION(collection)
{
  FACT(empty_ctor)
  {
    pepper::collection::builtin::empty::object<int> o;
  }

  FACT(empty_count)
  {
    pepper::collection::builtin::empty::object<int> o;

    EXPECT_EQ(o.count(), 0);
  }

  FACT(empty_foreach)
  {
    pepper::collection::builtin::empty::object<int> o;

    int sum = 256;

    pepper::collection::foreach(o) << [&] (int num)
    {
      sum += num;
    };

    EXPECT_EQ(sum, 256);
  }
}
