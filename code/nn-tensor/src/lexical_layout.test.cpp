#include <gtest/gtest.h>

#include "tensor/lexical_layout.h"

TEST(LexicalLayout, next)
{
  const tensor::shape shape{3, 5, 7};

  const tensor::index curr{1, 1, 1};
  const tensor::index next{1, 1, 2};

  const tensor::lexical_layout l;

  EXPECT_EQ(l.offset(shape, curr) + 1, l.offset(shape, next));
}

TEST(LexicalLayout, singleton)
{
  const tensor::shape shape{3, 5, 7};

  const tensor::index curr{1, 1, 1};
  const tensor::index next{1, 1, 2};

  const auto &l = tensor::lexical_layout::get();

  EXPECT_EQ(l.offset(shape, curr) + 1, l.offset(shape, next));
}
