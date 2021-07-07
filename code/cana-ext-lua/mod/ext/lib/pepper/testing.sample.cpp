#include <pepper/testing.hpp>

#include <iostream>

COLLECTION(sample)
{
  FACT(test_1)
  {
    std::cout << "Hello, World" << std::endl;

    bool bTrue = true;
    bool bFalse = false;

    EXPECT_TRUE(bTrue);
    EXPECT_TRUE(bFalse);
  }

  FACT(test_2)
  {
    std::cout << "Nice to meet you" << std::endl;

    bool bTrue = true;
    bool bFalse = false;

    EXPECT_FALSE(bFalse);
    EXPECT_FALSE(bTrue);
  }

  FACT(pass_EXPECT_EQ)
  {
    bool bLeft  = true;
    bool bRight = true;

    EXPECT_EQ(bLeft, bRight);
  }

  FACT(fail_EXPECT_EQ)
  {
    bool bLeft  = true;
    bool bRight = false;

    EXPECT_EQ(bLeft, bRight);
  }

  FACT(pass_EXPECT_NE)
  {
    bool bLeft  = true;
    bool bRight = false;

    EXPECT_NE(bLeft, bRight);
  }

  FACT(fail_EXPECT_NE)
  {
    bool bLeft  = true;
    bool bRight = true;

    EXPECT_NE(bLeft, bRight);
  }
}
