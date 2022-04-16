#include <gtest/gtest.h>

#include "filter/buffer.h"
#include "filter/NCHW_layout.h"

using filter::NCHW_layout;

TEST(filter_buffer, ctor)
{
  const filter::shape filter_shape{1, 1, 2, 2};
  filter::buffer<int> buffer{filter_shape, NCHW_layout{}};
}
