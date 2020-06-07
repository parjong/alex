#include <gtest/gtest.h>

#include "pepper/strcast.hpp"

using namespace pepper;

TEST(SafeStrCastTests, convert_int)
{
  ASSERT_EQ(safe_strcast<int>(nullptr, 32), 32);
  ASSERT_EQ(safe_strcast<int>("100", 32), 100);
}
