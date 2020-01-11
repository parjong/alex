#include <gtest/gtest.h>

#include "tensor/index.h"

TEST(Index, default_ctor)
{
  const tensor::index index;

  ASSERT_EQ(index.rank(), 0);
}

TEST(Index, initializer_ctor)
{
  const tensor::index index{1, 2, 3, 4};

  ASSERT_EQ(index.rank(), 4);
  ASSERT_EQ(index.at(0), 1);
  ASSERT_EQ(index.at(1), 2);
  ASSERT_EQ(index.at(2), 3);
  ASSERT_EQ(index.at(3), 4);
}
