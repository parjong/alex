#include <gtest/gtest.h>

#include "filter/shape.h"

TEST(filter_shape, default_ctor)
{
  const filter::shape shape{};

  ASSERT_EQ(shape.count(), 0);
  ASSERT_EQ(shape.depth(), 0);
  ASSERT_EQ(shape.height(), 0);
  ASSERT_EQ(shape.width(), 0);
}

TEST(filter_shape, value_ctor)
{
  const filter::shape shape{1, 2, 3, 4};

  ASSERT_EQ(shape.count(), 1);
  ASSERT_EQ(shape.depth(), 2);
  ASSERT_EQ(shape.height(), 3);
  ASSERT_EQ(shape.width(), 4);
}
