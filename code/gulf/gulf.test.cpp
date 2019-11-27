#include "gulf.hpp"

#include <gtest/gtest.h>

TEST(StreamTests, top_level_function)
{
  SUCCEED();
}

#if 0
namespace
{

int dec(int n) { return n - 1; }

} // namespace

TEST(FunctionPipeTests, static_method)
{
  struct Sample
  {
    static int dbl(int n) { return n * 2; }
  };

  ASSERT_EQ(4 | fipe::wrap(Sample::dbl), 8);
}

TEST(FunctionPipeTests, normal_method)
{
  struct Sample
  {
  public:
    int shift(int n) { return n + shiftamt; }

  private:
    int shiftamt = 6;
  };

  using namespace std::placeholders;

  Sample s;

  auto value = 4 | std::bind(&Sample::shift, &s, _1);

  ASSERT_EQ(value, 10);
}

TEST(FunctionPipeTests, lambda)
{
  auto inc = [] (int n) { return n + 1; };
  ASSERT_EQ(4 | inc, 5);
}

TEST(FunctionPipeTests, functor)
{
  ASSERT_EQ(4 | std::negate<int>(), -4);
}
#endif
