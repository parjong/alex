#include <gtest/gtest.h>

#include "filter/view_impl.h"
#include "filter/NCHW_layout.h"

TEST(filter_view_impl, copyable)
{
  const filter::shape filter_shape{1, 1, 3, 3};

  filter::view_impl<float> filter_view_1{filter_shape, filter::NCHW_layout{}};
  filter::view_impl<float> filter_view_2 = filter_view_1;
}
