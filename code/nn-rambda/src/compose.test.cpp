#include <gtest/gtest.h>

#include "rambda/compose.h"

TEST(COMPOSE, two)
{
  rambda::Fn<int, int> f = [] (int n) { return n + 1; };
  rambda::Fn<int, float> g = [] (int n) { return n + 1.3; };

  auto composed = rambda::compose(f, g);

  ASSERT_FLOAT_EQ(composed(3), 5.3);
}

TEST(COMPOSE, three)
{
  rambda::Fn<int, int> f = [] (int n) { return n + 2; };
  rambda::Fn<int, int> g = [] (int n) { return n + 3; };
  rambda::Fn<int, std::string> h = [] (int n)
  {
    return (n == 0) ? "zero" : "non-zero";
  };

  auto composed = rambda::compose(f, g, h);

  ASSERT_EQ(composed(3), "non-zero");
}
