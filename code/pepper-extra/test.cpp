#include "pepper/logging.hpp"

#include "gtest/gtest.h"

int main(int argc, char **argv) 
{
  // Configure logger(s)
  pepper::logging::configure();

  // Run all tests
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
