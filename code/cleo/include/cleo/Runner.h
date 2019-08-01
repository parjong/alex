#ifndef __CLEO_RUNNER_H__
#define __CLEO_RUNNER_H__

#include "cleo/App.h"

#include <memory>

namespace cleo
{

class Runner final
{
public:
  Runner(const App *app) : _app{app}
  {
    // DO NOTHING
  }

public:
  Runner &as(const std::string &name);

public:
  int with(int argc, const char * const * argv) const;

private:
  const App *_app;

  struct IDGenerator
  {
    virtual ~IDGenerator() = default;

    virtual std::string generate(void) const = 0;
  };

  std::unique_ptr<IDGenerator> _generator = nullptr;
};

inline Runner run(const App *app) { return Runner{app}; }

} // namespace cleo

#endif // __CLEO_RUNNER_H__
