#include <gtest/gtest.h>

#include "pepper/stream/array.hpp"
#include "pepper/optparse/opt/base.hpp"
#include "pepper/optparse/opt/required.hpp"
#include "pepper/optparse/parser.hpp"

TEST(optparse, required_string)
{
  std::string values[] = {
    "value",
  };

  pepper::stream::array<std::string> stream{ values, 1 };

  pepper::optparse::opt::required<std::string> stropt{ };
  
  EXPECT_EQ( stropt.take(stream), true );
  EXPECT_EQ( stropt(), values[0] );
}

TEST(optparse, parser)
{
  pepper::optparse::parser op;

  pepper::optparse::opt::required<std::string> stropt{ };

  op.add_longopt("name", stropt);
  
  //
  std::string args[] = {
    "--name", 
    "hello"
  };

  pepper::stream::array<std::string> stream{ args, 2 };
  
  op.parse(stream);

  EXPECT_EQ( stropt(), args[1] );
  EXPECT_NE( stropt(), "aaa" );
}

