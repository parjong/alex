#include <pepper/testing.hpp>
#include <pepper/maybe.hpp>

COLLECTION(maybe)
{ 
  FACT(equality)
  {
    EXPECT_NE(pepper::maybe::none<int>(), 3);

    EXPECT_EQ(pepper::maybe::some<int>(3), 3);
    EXPECT_NE(pepper::maybe::some<int>(3), 5);

    EXPECT_EQ(3, pepper::maybe::some<int>(3));
    EXPECT_NE(5, pepper::maybe::some<int>(3));
  }

  FACT(map_lambda)
  {
    auto succ = [] (int num)
    {
      return num + 1;
    };

    EXPECT_EQ(pepper::maybe::some<int>(3).map<int>(succ), 4);
  }

  int succ(int num)
  {
    return num + 1;
  }

  FACT(map_function)
  {
    EXPECT_EQ(pepper::maybe::some<int>(3).map<int>(succ), 4);
  }

}
