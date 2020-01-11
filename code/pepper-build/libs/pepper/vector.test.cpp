#include <pepper/testing.hpp>
#include <pepper/vector.hpp>

COLLECTION(vector)
{
  FACT(pod_element)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(3);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 3);

    vec.at(0) = 2;

    EXPECT_EQ(vec.at(0), 2);
  }

  FACT(pod_foreach)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(3);

    int sum = 0;

    pepper::collection::foreach(vec) << [&sum] (const int &num)
    {
      sum += num;
    };

    EXPECT_EQ(sum, 4);
  }

  bool is_odd(const int num)
  {
    return num % 2 != 0;
  }

  FACT(pod_forall_true)
  {
    pepper::vector::object<int> vec;

    vec.emplace(1).emplace(3);

    EXPECT_TRUE(pepper::collection::forall(vec) << is_odd);

    vec.emplace(4);

    EXPECT_FALSE(pepper::collection::forall(vec) << is_odd);
  }

  FACT(copy)
  {
    pepper::vector::object<int> from;

    from.emplace(1).emplace(2);

    EXPECT_EQ(from.size(), 2);

    pepper::vector::object<int> into = from;

    EXPECT_EQ(into.size(), 2);

    from.emplace(3);

    EXPECT_EQ(from.size(), 3);
    EXPECT_EQ(into.size(), 2);
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
    pepper::vector::object<std::unique_ptr<number>> vec;

    vec.emplace(pepper::mem::unique::make<number>(3));

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.at(0)->value, 3);
  }

  FACT(non_copyable_foreach)
  {
    pepper::vector::object<std::unique_ptr<number>> vec;

    vec.emplace(pepper::mem::unique::make<number>(3));
    vec.emplace(pepper::mem::unique::make<number>(4));

    int sum = 0;

    pepper::collection::foreach(vec) << [&sum] (const std::unique_ptr<number> &num)
    {
      sum += num->value;
    };

    EXPECT_EQ(sum, 7);
  }
}
