#include <pepper/testing.hpp>
#include <pepper/exn.hpp>

COLLECTION(exn)
{
  FACT(handle)
  {
    std::string message;

    try
    {
      pepper::exn::raise(3, " + ", 3, " = ", 6);
    }
    catch (const std::exception &e)
    {
      message = e.what();
    }

    EXPECT_EQ(message, "3 + 3 = 6");
  }

  FACT(raise_if_throw)
  {
    std::string orig{"3 + 4 = 7"};
    std::string copy{orig};

    try
    {
      pepper::exn::raise_if(true, 3, " + ", 3, " = ", 6);
    }
    catch (const std::exception &e)
    {
      orig = e.what();
    }

    EXPECT_NE(orig, copy);
  }

  FACT(raise_if_nothrow)
  {
    std::string orig{"3 + 4 = 7"};
    std::string copy{orig};

    try
    {
      pepper::exn::raise_if(false, 3, " + ", 3, " = ", 6);
    }
    catch (const std::exception &e)
    {
      orig = e.what();
    }

    EXPECT_EQ(orig, copy);
  }

  FACT(raise_unless_throw)
  {
    std::string orig{"3 + 4 = 7"};
    std::string copy{orig};

    try
    {
      pepper::exn::raise_unless(false, 3, " + ", 3, " = ", 6);
    }
    catch (const std::exception &e)
    {
      orig = e.what();
    }

    EXPECT_NE(orig, copy);
  }

  FACT(raise_unless_nothrow)
  {
    std::string orig{"3 + 4 = 7"};
    std::string copy{orig};

    try
    {
      pepper::exn::raise_unless(true, 3, " + ", 3, " = ", 6);
    }
    catch (const std::exception &e)
    {
      orig = e.what();
    }

    EXPECT_EQ(orig, copy);
  }
}
