#include <pepper/testing.hpp>
#include <pepper/optional.hpp>

COLLECTION(optional)
{
  FACT(empty_constructor)
  {
    pepper::optional::object<int> m;

    EXPECT_FALSE(m.filled());
  }

  FACT(value_constructor)
  {
    pepper::optional::object<int> m{128};

    EXPECT_TRUE(m.filled());
    EXPECT_EQ(m.get(256), 128);
  }

  FACT(set)
  {
    pepper::optional::object<int> m;

    EXPECT_FALSE(m.filled());

    m.set(64);

    EXPECT_TRUE(m.filled());
    EXPECT_EQ(m.get(256), 64);
  } 

  FACT(set_nested)
  {
    pepper::optional::object<int> m;

    EXPECT_FALSE(m.filled());
    EXPECT_EQ(m.set(64).get(256), 64);
  }

  FACT(map)
  {
    pepper::optional::object<int> m{128};

    auto is_odd = [] (int n)
    {
      return n % 2 == 0;
    };

    EXPECT_TRUE(m.map<bool>(is_odd).get(false));
  } 

  FACT(read)
  {
    pepper::optional::object<int> m;

    int num = 0;

    auto accum = [&] (int value)
    {
      num += value;
    };

    EXPECT_FALSE(m.read(accum));
    EXPECT_EQ(num, 0);

    EXPECT_TRUE(m.set(128).read(accum));
    EXPECT_EQ(num, 128);
  }

  FACT(rewrite)
  {
    pepper::optional::object<int> m;

    auto double_num = [&] (int &value)
    {
      value = value * 2;
    };

    EXPECT_FALSE(m.filled());
    EXPECT_FALSE(m.rewrite(double_num).filled());

    EXPECT_TRUE(m.set(64).filled());
    EXPECT_EQ(m.get(256), 64);

    EXPECT_TRUE(m.rewrite(double_num).filled());
    EXPECT_EQ(m.get(256), 128);
  }

  FACT(replace)
  {
    pepper::optional::object<int> m{128};

    m.replace([] (int n) { return n / 2; });

    EXPECT_EQ(m.get(256), 64);
  }

  FACT(join)
  {
    auto tf = [] (int n)
    {
      return n + 1;
    };

    auto ff = [] (void)
    {
      return 0;
    };

    pepper::optional::object<int> some{1};

    EXPECT_EQ(some.join<int>(tf, ff), 2);

    pepper::optional::object<int> none{};

    EXPECT_EQ(none.join<int>(tf, ff), 0);
  }

  FACT(operator_assign)
  {
    pepper::optional::object<int> m;

    EXPECT_FALSE(m.filled());

    m = 128;

    EXPECT_TRUE(m.filled());
    EXPECT_EQ(m.get(256), 128);
  }
}
