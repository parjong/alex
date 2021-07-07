#include <gtest/gtest.h>

#include "tensor/overlay.h"
#include "tensor/lexical_layout.h"

TEST(overlay, ctor)
{
  using tensor::shape;
  using tensor::lexical_layout;

  int data[2 * 3 * 4 * 5] = { 0, };

  tensor::overlay<int> o{shape{2,3,4,5}, lexical_layout{}, data};

  EXPECT_EQ(o.data(), data);
}

TEST(overlay, factory)
{
  using tensor::shape;
  using tensor::lexical_layout;

  int data[2 * 3 * 4 * 5] = { 0, };

  auto o = tensor::overlay_factory<lexical_layout>::make(shape{2,3,4,5}, data);

  EXPECT_EQ(o.data(), data);
}
