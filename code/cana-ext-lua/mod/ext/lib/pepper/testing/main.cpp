#include <pepper/testing/core.hpp>

#include <iostream>

int main(int argc, char **argv) 
{
  int total  = 0;
  int passed = 0;
  int failed = 0;

  auto access_fn = [&](const pepper::testing::base::suite *suite)
  {
    auto running_fn = [&](const pepper::testing::base::unit *unit)
    {
      try
      {
        unit->run();
        std::cerr << "'" << unit->name() << "' passed (from '" << suite->name() << "')" << std::endl;
        ++passed;
      }
      catch (const pepper::testing::core::error &err)
      {
        std::cerr << "'" << unit->name() << "' failed (from '" << suite->name() << "')" << std::endl;
        std::cerr << err.message() << std::endl;
        ++failed;
      }

      ++total;
    };

    suite->foreach(running_fn);
 };

  pepper::testing::core::catalog::instance().foreach(access_fn);

  std::cout << "Total: " << total << ", Passed: " << passed << ", Failed: " << failed << std::endl;

  return (failed > 0) ? 100 : 0;
}
