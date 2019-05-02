#include "cleo/Runner.h"

namespace
{

class BlockArgs final : public cleo::Args
{
public:
  BlockArgs(int argc, const char * const *argv)
  {
    _argc = static_cast<uint32_t>(argc);
    _argv = argv;
  }

public:
  uint32_t count(void) const final { return _argc; }
  std::string value(uint32_t n) const final { return _argv[n]; }

private:
  uint32_t _argc;
  const char * const *_argv;
};

} // namespace

namespace cleo
{

Runner &Runner::as(const std::string &name)
{
  struct IDGeneratorImpl final : public IDGenerator
  {
  public:
    IDGeneratorImpl(const std::string &value) : _value{value}
    {
      // DO NOTHING
    }

  public:
    std::string generate(void) const final { return _value; }

  private:
    std::string _value;
  };

  _generator = std::make_unique<IDGeneratorImpl>(name);

  return (*this);
}

int Runner::with(int argc, const char * const * argv) const
{
  std::string id = argv[0];

  if (_generator)
  {
    id = _generator->generate(); 
  }

  BlockArgs args{argc - 1, argv + 1};

  return _app->run(nullptr, id, &args);
}

} // namespace cleo
