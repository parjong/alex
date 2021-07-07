#include <pepper/testing.hpp>
#include <pepper/vector.hpp>
#include <pepper/view.hpp>

COLLECTION(viewtests)
{
  FACT(usage)
  {
    auto vec = pepper::mem::shared::make<std::vector<int>>();

    vec->push_back(3);
    vec->push_back(4);
    vec->push_back(5);
    vec->push_back(6);

    pepper::vector::cursor::object<int> vs{ vec };
    pepper::view::cursor<int> ls{ vs };

    EXPECT_EQ(ls.access(0), (*vec)[0]);
    EXPECT_EQ(ls.access(1), (*vec)[1]);
    EXPECT_EQ(ls.access(2), (*vec)[2]);
    EXPECT_EQ(ls.access(3), (*vec)[3]);
    EXPECT_FALSE(ls.access(4).filled());

    ls.forward(1);

    EXPECT_EQ(ls.access(0), (*vec)[1]);
  }
}
