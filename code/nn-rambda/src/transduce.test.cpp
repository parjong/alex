#include <gtest/gtest.h>

#include "rambda/transduce.h"

using namespace rambda;

TEST(TRANSDUCE, sink_seq)
{
  int accum = 0;

  CSink<int> sink = [&accum] (int num)
  {
    accum += num;
  };

  auto seq = sink::seq(sink, sink, sink);

  seq(4);

  ASSERT_EQ(accum, 12);
}

namespace
{
template<typename T> CSink<T> make_sink(const T &expected)
{
  return [expected] (const T &obtained)
  {
    ASSERT_EQ(obtained, expected);
  };
}
} // namespace

TEST(TRANSDUCE, xform_unit)
{
  auto xform = xform::unit<int>();

  xform(make_sink<int>(0))(0);
  xform(make_sink<int>(1))(1);
}

TEST(TRANSDUCE, xform_map)
{
  auto xform = xform::map<int, std::string>([] (float n) { return (n == 0) ? "Z" : "NZ"; });

  xform(make_sink<std::string>("Z"))(0);
  xform(make_sink<std::string>("NZ"))(1);
}

TEST(TRANSDUCE, xform_filter)
{
  uint32_t count = 0;

  CSink<int> counter = [&count] (int)
  {
    count += 1;
  };

  auto xform = xform::filter<int>([] (int n) { return (n == 0); });

  xform(counter)(1);
  ASSERT_EQ(count, 0);

  xform(counter)(0);
  ASSERT_EQ(count, 1);
}

TEST(TRANSDUCE, xform_compose_two)
{
  auto xform_1 = xform::map<int, float>([] (int n) { return n + 0.2f; });
  auto xform_2 = xform::map<float, std::string>([] (float n) { return (n > 0.0f) ? "P" : "N"; });

  auto composed = xform::compose(xform_1, xform_2);

  Sink<std::string> sink = [] (const std::string &v)
  {
    ASSERT_EQ(v, "P");
  };

  composed(sink)(3);
}

TEST(TRANSDUCE, xform_compose_three)
{
  auto xform_1 = xform::map<int, int>([] (int n) { return n + 1; });
  auto xform_2 = xform::map<int, int>([] (int n) { return n + 2; });
  auto xform_3 = xform::map<int, int>([] (int n) { return n + 3; });

  auto composed = xform::compose(xform_1, xform_2, xform_3);

  composed(make_sink<int>(7))(1);
}

TEST(TRANSDUCE, transduce)
{
  auto xform = xform::unit<int>();

  int accum = 0;

  Sink<int> sink = [&accum] (int num)
  {
    accum += num;
  };

  transduce(std::initializer_list<int>{1, 2, 3, 4}, xform, sink);

  ASSERT_EQ(accum, 10);
}
