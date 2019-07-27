#include <gtest/gtest.h>

#include "pepper/str.hpp"

using namespace pepper;

TEST(StrTests, str_int)
{
  // Get a "string" value from an "int" value
  ASSERT_EQ(str(100), "100");
}

TEST(StrTests, str_int_and_string)
{
  // Concatenate "int", C-string, and "int"
  ASSERT_EQ(str(100, " and ", 200), "100 and 200");
}
