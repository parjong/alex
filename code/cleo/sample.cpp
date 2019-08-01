#include "cleo.h"

#include <iostream>

using namespace cleo;

struct HelloWorldApp final : public StandaloneApp
{
  int run(const Args *) const final
  {
    std::cout << "Hello, World" << std::endl;
    return 0;
  }
};

int main(int argc, char **argv)
{
  HelloWorldApp app;
  return cleo::run(&app).with(argc, argv);
}
