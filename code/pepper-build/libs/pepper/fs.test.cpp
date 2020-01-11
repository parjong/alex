#include <pepper/testing.hpp>
#include <pepper/fs.hpp>

COLLECTION(fs)
{
  FACT(usage)
  {
    pepper::fs::sys::service fl;

    const std::string p{ "SAMPLE" };
    const std::string expected{ "Hello!!" };

    bool made = fl.file().make(p) << [&] (std::ostream &os)
    {
      os << expected << std::endl;
    };

    EXPECT_TRUE( made );

    bool read = fl.file().open(p) << [&] (std::istream &is)
    {
      std::string obtained;

      is >> obtained;

      EXPECT_EQ( expected, obtained );
    };

    EXPECT_TRUE( read );
  }

  FACT(notfound)
  {
    pepper::fs::sys::service fl;

    bool read = fl.file().open("NOTFOUND") << [] (std::istream &is)
    {
      return;
    };

    EXPECT_FALSE( read );
  }
}
