#include <gtest/gtest.h>

#include "filter/overlay.h"
#include "filter/NCHW_layout.h"

using filter::NCHW_layout;

TEST(filter_overlay, over_array)
{
  const uint64_t N = 1;
  const uint64_t C = 1;
  const uint64_t H = 2;
  const uint64_t W = 2;

  int data[1 * 1 * 2 * 2] = { 0, 1, 2, 3 };

  const filter::shape shape{1, 1, 2, 2};
  auto overlay = filter::overlay_factory<int, NCHW_layout>::make(shape, data);

  ASSERT_EQ(overlay.at(0, 0, 0, 0), 0);
  ASSERT_EQ(overlay.at(0, 0, 0, 1), 1);
  ASSERT_EQ(overlay.at(0, 0, 1, 0), 2);
  ASSERT_EQ(overlay.at(0, 0, 1, 1), 3);
}

TEST(filter_overlay, overlay_over_vector)
{
  const uint64_t N = 1;
  const uint64_t C = 1;
  const uint64_t H = 2;
  const uint64_t W = 2;

  std::vector<int> data{0, 1, 2, 3};

  const filter::shape shape{1, 1, 2, 2};
  auto overlay = filter::overlay_factory<int, NCHW_layout>::make(shape, data.begin());

  ASSERT_EQ(overlay.at(0, 0, 0, 0), 0);
  ASSERT_EQ(overlay.at(0, 0, 0, 1), 1);
  ASSERT_EQ(overlay.at(0, 0, 1, 0), 2);
  ASSERT_EQ(overlay.at(0, 0, 1, 1), 3);
}
