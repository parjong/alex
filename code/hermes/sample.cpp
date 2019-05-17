#include <hermes.h>

#include <iostream>

using namespace hermes;

// Each client SHOULD implement its own configuration loader

// TODO Make this reusable
// NOTE LoggerConfig<BasicLogger> should be PUBLIC inheritance
struct MyConfig final : public Config, public SourceConfig<BasicLogger>
{
public:
  MyConfig()
  {
    auto env_p = std::getenv("ENABLE_LOGGING");

    if (env_p)
    {
      _flag = (std::stoi(env_p) != 0);
    }
    else
    {
      _flag = false;
    }
  }

private:
  void configure(const BasicLogger *, Source::Setting &setting) const override
  {
    if (_flag)
    {
      // Enable all catagories
      setting.accept_all();
    }
    else
    {
      // Disable all catagories
      setting.reject_all();
    }
  }

private:
  bool _flag = false;
};

hermes::Context *context(void)
{
  static hermes::Context *ctx = nullptr;

  if (ctx == nullptr)
  {
    ctx = new hermes::Context;
    ctx->config(std::make_unique<MyConfig>());
    ctx->sinks()->append(std::make_unique<ConsoleReporter>());
  }

  return ctx;
}

#define MY_LOGGER(name) hermes::BasicLogger name{context()};
#define MY_INFO(name) HERMES_INFO(name)

int main(int argc, char **argv)
{
  MY_LOGGER(s);

  printf("MARK\n");
  MY_INFO(s) << "Hello" << std::endl;

  return 0;
}
