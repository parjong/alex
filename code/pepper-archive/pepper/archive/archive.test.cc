#include "pepper/archive/archive.h"

#include <gtest/gtest.h>

#include <random>
#include <sstream>

TEST(archive, simple_int)
{
  std::default_random_engine engine;
  std::uniform_int_distribution<int> dist;

  const int num = dist(engine);

  const int src = num + 1;
  int dst = num - 1;

  std::stringstream stream;

  pepper::archive<int>::write(stream, src);
  pepper::archive<int>::read(stream, dst);

  ASSERT_EQ(src, dst);
}

TEST(archive, simple_uint)
{
  std::default_random_engine engine;
  std::uniform_int_distribution<unsigned int> dist;

  const unsigned int num = dist(engine);

  const unsigned int src = num + 1;
  unsigned int dst = num - 1;

  std::stringstream stream;

  pepper::archive<unsigned int>::write(stream, src);
  pepper::archive<unsigned int>::read(stream, dst);

  ASSERT_EQ(src, dst);
}
