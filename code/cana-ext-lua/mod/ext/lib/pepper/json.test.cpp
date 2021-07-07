#include <pepper/testing.hpp>
#include <pepper/logging.hpp>
#include <pepper/json.hpp>

#include <sstream>

namespace js = pepper::json::type;

COLLECTION(json)
{
  struct derived_object : public js::obj::value
  {
    js::str::field title;
    js::num::field number;
    js::seq::field<js::num::value> numbers;
    js::map::field<derived_object> children;

    derived_object() 
      : title{*this, "title"}
      , number{*this, "number"}
      , numbers{*this, "numbers"}
      , children{*this, "children"}
    {
      // DO NOTHING
    }
  };

  FACT(dump_derived_object)
  {
    /** Create a JSON object */
    derived_object obj;

    obj.title() = "under";

    obj.number() = 3;

    obj.numbers().emplace_back(3);
    obj.numbers().emplace_back(4);
    obj.numbers().emplace_back(5);

    obj.children().at("mine").number() = 4;

    /** Create a JSON value */
    std::cout << obj;
  }

  FACT(load_derived_object)
  {
    std::stringstream ss{"{ \"title\" : \"hello\", \"number\" : 3, \"numbers\" : [1, 2, 3] }"};

    derived_object obj;

    ss >> obj;

    EXPECT_EQ((const std::string &) obj.title(), "hello");
    EXPECT_EQ(obj.number(), 3);
    EXPECT_EQ(obj.numbers().size(), 3);
    EXPECT_EQ(obj.numbers().at(0), 1);
    EXPECT_EQ(obj.numbers().at(1), 2);
    EXPECT_EQ(obj.numbers().at(2), 3);

    std::cout << obj;
  }

  struct derived_map : public js::map::value<js::num::value>
  {
    derived_map() = default;
    virtual ~derived_map() = default;
  };

  FACT(dump_derived_map_empty)
  {
    derived_map obj;

    std::cout << obj;
  }

  FACT(dump_derived_map)
  {
    derived_map obj;

    obj.at("1st") = 3;

    std::cout << obj;
  }

  FACT(log_derived_object)
  {
    static pepper::logging::logger log{"json.log"};

    derived_object obj;

    log.trace( obj );
  }

  const derived_object &get_derived_object(void)
  {
    static derived_object obj;
    return obj;
  }

  FACT(log_returned_derived_object)
  {
    static pepper::logging::logger log{"json.log"};

    log.trace(::get_derived_object());
  }
}
