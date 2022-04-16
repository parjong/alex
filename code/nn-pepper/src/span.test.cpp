#include <gtest/gtest.h>

#include "pepper/span.h"

TEST(span, default_ctor)
{
  const pepper::span<int> span{};

  EXPECT_EQ(span.size(), 0);
}

TEST(span, value_ctor_from_array)
{
  int arr[3] = {1, 2, 3};

  const pepper::span<int> span{arr, 3};

  EXPECT_EQ(span.size(), 3);
  EXPECT_EQ(span.at(0), 1);
  EXPECT_EQ(span.at(1), 2);
  EXPECT_EQ(span.at(2), 3);
}
