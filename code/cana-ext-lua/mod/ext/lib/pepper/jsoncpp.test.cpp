#include <pepper/testing.hpp>
#include <pepper/jsoncpp.hpp>
#include <pepper/jview.hpp>

#include <sstream>
#include <set>

COLLECTION(jsoncpp)
{
  struct derived : public pepper::jview::obj
  {
    pepper::jview::str::fld string;
    pepper::jview::num::fld number;
    pepper::jview::seq::fld numbers;

    derived()
      : string{*this, "string"}
      , number{*this, "number"}
      , numbers{*this, "numbers"}
    {
      // DO NOTHING
    }
    virtual ~derived() = default;
  };

  FACT(image)
  {
    std::stringstream ss{"{ \"string\" : \"hello\", \"number\" : 3, \"numbers\" : [1, 2, 3] }"};

    auto image = pepper::jsoncpp::image::make(ss);

    {
      auto check_fn = [] (const std::string &s)
      {
        EXPECT_EQ(s, "hello");
      };

      image.read(pepper::jpath::make().named("string"), check_fn);
    }

    {
      auto check_fn = [] (int n)
      {
        EXPECT_EQ(n, 3);
      };

      image.read(pepper::jpath::make().named("number"), check_fn);
    }

    for (int i = 0; i < 3; ++i)
    {
      auto check_fn = [=] (int n)
      {
        EXPECT_EQ(n, i + 1);
      };

      image.read(pepper::jpath::make().named("numbers").indexed(i), check_fn);
    }
  }

  FACT(jview)
  {
    std::stringstream ss{"{ \"string\" : \"hello\", \"number\" : 3, \"numbers\" : [1, 2, 3] }"};

    auto image = pepper::jsoncpp::image::make(ss);

    derived d;

    d.string.read(image) << [] (const std::string &s)
    {
      EXPECT_EQ(s, "hello");
    };

    d.number.read(image) << [] (int num)
    {
      EXPECT_EQ(num, 3);
    };

    std::set<int> indexes;
    std::set<int> values;

    d.numbers.read(image) << [&] (const pepper::jpath::object &p, int index, const pepper::jimage::object &o)
    {
      indexes.insert(index);

      auto value_fn = [&] (int num)
      {
        values.insert(num);
      };

      o.read(pepper::jpath::make(), value_fn);
    };

    EXPECT_EQ(indexes.size(), 3);
    EXPECT_NE(indexes.find(0), indexes.end());
    EXPECT_NE(indexes.find(1), indexes.end());
    EXPECT_NE(indexes.find(2), indexes.end());
  }
}
