#include <gtest/gtest.h>

#include "tensor/shape.h"

TEST(Shape, default_ctor)
{
  tensor::shape shape;

  ASSERT_EQ(shape.rank(), 0);
}

TEST(Shape, initializer_ctor)
{
  tensor::shape shape{1, 2, 3, 4};

  ASSERT_EQ(shape.rank(), 4);
  ASSERT_EQ(shape.dim(0), 1);
  ASSERT_EQ(shape.dim(1), 2);
  ASSERT_EQ(shape.dim(2), 3);
  ASSERT_EQ(shape.dim(3), 4);
}

TEST(Shape, resize)
{
  tensor::shape shape;

  ASSERT_EQ(shape.rank(), 0);
  shape.resize(4);
  ASSERT_EQ(shape.rank(), 4);
}
