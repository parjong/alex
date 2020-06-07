#include <cleo/App.h>
#include <cleo/Runner.h>
#include <cleo/AtomApp.h>
#include <cleo/SelectorApp.h>

#include <iostream>

#include <map>
#include <memory>

#include <stdexcept>

namespace
{

struct HelloWorldApp final : public cleo::AtomApp
{
  int run(const cleo::Args *) const final
  {
    std::cout << "Hello, World!!" << std::endl;
    return 0;
  }
};

} // namespace

int main(int argc, char **argv)
{
  cleo::SelectorApp app;

  app.command("hello").entry(std::make_unique<HelloWorldApp>());
  app.command("help").entry(std::make_unique<cleo::HelpCommand>());

  return cleo::run(app).with(argc, argv);
}
