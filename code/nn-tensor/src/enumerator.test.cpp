#include <gtest/gtest.h>

#include <array>
#include <algorithm>

#include "tensor/enumerator.h"

TEST(Enumerator, loop)
{
  const tensor::shape shape{3, 4};

  std::array<int, 3 * 4> arr;

  arr.fill(0);

  for(tensor::enumerator e{shape}; e.valid(); e.next())
  {
    const auto &index = e.curr();

    arr[index.at(0) * 4 + index.at(1)] += 2;
  }

  ASSERT_TRUE(std::all_of(arr.begin(), arr.end(), [] (int n) { return n == 2; }));
}
