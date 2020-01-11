#include <pepper/testing.hpp>

#include <pepper/array.hpp>
#include <pepper/mem.hpp>

COLLECTION(array)
{
  FACT(pod_element)
  {
    pepper::array::object<int, 4> arr;

    arr.raw().at(0) = 0;

    EXPECT_EQ( arr.raw().at(0), 0 );
  }

  struct number
  {
    int value;

    number(int n) : value{n}
    {
      // DO NOTHING
    }
  };

  FACT(non_copyable_element)
  {
    pepper::array::object<std::unique_ptr<number>, 4> arr;

    arr.raw().at(0) = pepper::mem::unique::make<number>(3);

    EXPECT_EQ(arr.raw().at(0)->value, 3);
  }

  FACT(deep_copy_semantics)
  {
    pepper::array::object<int, 2> from;

    from.raw().at(0) = 10;
    from.raw().at(1) = 20;

    pepper::array::object<int, 2> into = from;

    EXPECT_EQ(into.raw().at(0), 10);
    EXPECT_EQ(into.raw().at(1), 20);

    into.raw().at(1) = 30;

    EXPECT_EQ(from.raw().at(1), 20);
    EXPECT_EQ(into.raw().at(1), 30);
  }

  FACT(cursor)
  {
    pepper::array::object<int, 4> arr;

    arr.raw().at(0) = 3;
    arr.raw().at(1) = 4;
    arr.raw().at(2) = 5;
    arr.raw().at(3) = 6;

    auto cursor = arr.collection().cursor();

    EXPECT_EQ(cursor.access(0), arr.raw().at(0));
    EXPECT_EQ(cursor.access(1), arr.raw().at(1));
    EXPECT_EQ(cursor.access(2), arr.raw().at(2));
    EXPECT_EQ(cursor.access(3), arr.raw().at(3));
    EXPECT_FALSE(cursor.access(4).filled());

    cursor.forward(1);

    EXPECT_EQ(cursor.access(0), arr.raw().at(1));
  }
}
