#include <pepper/testing.hpp>
#include <pepper/env.hpp>

COLLECTION(env)
{
  FACT(ctor)
  {
    pepper::env::reader r{"VARIABLE"};
  }

  FACT(system_set_get)
  {
    pepper::env::system::object obj;

    const std::string k = "SAMPLE";
    const std::string v = "HELLO?";

    obj.set(k) = v;
    EXPECT_EQ(obj.get(k), v);
  }
}
