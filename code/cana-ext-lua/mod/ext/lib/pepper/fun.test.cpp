#include <pepper/testing.hpp>
#include <pepper/fun.hpp>

COLLECTION(fun)
{ 
  bool is_even(int n)
  {
    return n % 2 == 0;
  }

  FACT(pred_neg)
  {
    EXPECT_TRUE(pepper::fun::pred::neg<int>(is_even)(1));
    EXPECT_FALSE(pepper::fun::pred::neg<int>(is_even)(2));
  }

  FACT(pred_gt)
  {
    auto is_gt_two = pepper::fun::pred::gt(2);

    EXPECT_TRUE(is_gt_two(3));
    EXPECT_FALSE(is_gt_two(2));
    EXPECT_FALSE(is_gt_two(1));
  }

  FACT(pred_ge)
  {
    auto is_ge_two = pepper::fun::pred::ge(2);

    EXPECT_TRUE(is_ge_two(2));
    EXPECT_TRUE(is_ge_two(3));
    EXPECT_FALSE(is_ge_two(1));
  }

  FACT(pipe_bind_lambda)
  {
    auto succ = [] (const int &n) -> int
    {
      return n + 1;
    };

    EXPECT_EQ(pepper::fun::pipe::make(1).bind<int>(succ), 2);
    EXPECT_EQ(pepper::fun::pipe::make(1).bind<int>(succ).bind<int>(succ), 3);
  }

  int succ(int n)
  {
    return n + 1;
  }

  FACT(pipe_bind_function)
  {
    EXPECT_EQ(pepper::fun::pipe::make(1).bind<int>(succ), 2);
  }

  FACT(finally_run)
  {
    int sum = 0;

    {
      auto incr = [&] (void)
      {
        ++sum;
      };

      pepper::fun::finally o{incr};

      EXPECT_EQ(sum, 0);
    }

    EXPECT_EQ(sum, 1);
  }
}
