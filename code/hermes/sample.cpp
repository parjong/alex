#include <hermes.h>

#include <iostream>

using namespace hermes;

namespace
{

struct SampleConfig final : public Config
{
public:
  SampleConfig()
  {
    auto env_p = std::getenv("LOG");

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
  void configure(const Source *, Filter &f) const override
  {
    if (_flag)
    {
      // Enable all catagories
      f.apply(accept_all_rule()).to(all_groups());
    }
    else
    {
      // Disable all catagories
      f.apply(deny_all_rule()).to(all_groups());
    }
  }

private:
  bool _flag = false;
};

struct SampleLogger final : public Source
{
  SampleLogger(Context *ctx) { activate(ctx); }
  ~SampleLogger() { deactivate(); }
};

struct SampleReporter final : public Sink
{
  void notify(const Log *m) override
  {
    std::cout << m->severity()->group() << std::endl;
    for (uint32_t n = 0; n < m->msg()->lines(); ++n)
    {
      std::cout << "  " << m->msg()->line(n) << std::endl;
    }
  }
};

hermes::Context *context(void)
{
  static hermes::Context *ctx = nullptr;

  if (ctx == nullptr)
  {
    ctx = new hermes::Context;
    ctx->config(std::make_unique<SampleConfig>());
    ctx->sinks()->append(std::make_unique<SampleReporter>());
  }

  return ctx;
}

} // namespace

#define LOGGER(name) ::SampleLogger name{context()};
#define INFO(name) HERMES_INFO(name)

int main(int argc, char **argv)
{
  LOGGER(s);

  INFO(s) << "Nice to meet you!" << std::endl;

  return 0;
}
