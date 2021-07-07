#include <gtest/gtest.h>

#include "stdex/set.h"

TEST(set, make_set_constant)
{
  auto s = stdex::make_set<int>(1, 2);

  ASSERT_EQ(s.size(), 2);

  ASSERT_NE(s.find(1), s.end());
  ASSERT_NE(s.find(2), s.end());

  ASSERT_EQ(s.find(0), s.end());
}

TEST(set, make_set_iterator)
{
  int arr[3] = { 1, 2, 3 };

  auto s = stdex::make_set<int>(arr, arr + 3);

  ASSERT_EQ(s.size(), 3);

  ASSERT_NE(s.find(1), s.end());
  ASSERT_NE(s.find(2), s.end());
  ASSERT_NE(s.find(3), s.end());

  ASSERT_EQ(s.find(0), s.end());
}

TEST(set, eq)
{
  using stdex::make_set;

  ASSERT_TRUE(make_set<int>(1, 2, 3) == make_set<int>(1, 2, 3));

  ASSERT_FALSE(make_set<int>(1) == make_set<int>(1, 2, 3));
  ASSERT_FALSE(make_set<int>(1, 2) == make_set<int>(1, 3));
}

TEST(set, diff)
{
  using stdex::make_set;

  auto s = make_set<int>(1, 2, 3) - make_set<int>(2);

  ASSERT_EQ(s.size(), 2);
  ASSERT_NE(s.find(1), s.end());
  ASSERT_EQ(s.find(2), s.end());
  ASSERT_NE(s.find(3), s.end());
}
