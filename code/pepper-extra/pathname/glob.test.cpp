#include "pepper/pathname/glob.hpp"

#include <gtest/gtest.h>

TEST(PathnameGlob, FlatSimple) {
  pepper::pathname::glob glob{ "aaa" };

  EXPECT_EQ( glob.is_matched( "aaa" ), true );
  EXPECT_EQ( glob.is_matched( "abb" ), false );
}

TEST(PathnameGlob, FlatAsterisk) {
  pepper::pathname::glob glob{ "a*a" };

  EXPECT_EQ( glob.is_matched( "aaa" ), true );
  EXPECT_EQ( glob.is_matched( "abca" ), true );
  EXPECT_EQ( glob.is_matched( "abcab" ), false );
}

TEST(PathnameGlob, RecusriveSimple) {
  pepper::pathname::glob glob{ "**/*.cs" };

  EXPECT_EQ( glob.is_matched( "a.cs" ), true );
  EXPECT_EQ( glob.is_matched( "aaa/bbb/a.cs" ), true );
  EXPECT_EQ( glob.is_matched( "c.cpp" ), false );
  EXPECT_EQ( glob.is_matched( "aaa/bbb/c.cpp" ), false );
}

TEST(PathnameGlob, RecusriveNested) {
  pepper::pathname::glob glob{ "**/src/**/*.cs" };

  EXPECT_EQ( glob.is_matched( "a.cs" ), false );
  EXPECT_EQ( glob.is_matched( "aaa/src/bbb/a.cs" ), true );
}
