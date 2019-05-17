#ifndef __HERMES_CONTEXT_H__
#define __HERMES_CONTEXT_H__

#include "hermes/Log.h"
#include "hermes/Filter.h"
#include "hermes/Source.h"
#include "hermes/Sink.h"

#include <memory>
#include <set>

namespace hermes
{

/**
 * @brief Source Configuration
 */
struct Config
{
  virtual ~Config() = default;

  virtual void configure(const Source *, Filter &) const = 0;
};

/**
 * @brief Global Logging Context
 */
class Context final : private Bus, private SourceRegistry, private SinkRegistry
{
public:
  const Config *config(void) const { return _config.get(); }

  void config(std::unique_ptr<Config> &&config)
  {
    _config = std::move(config);

    // Apply updated configurations
    for (auto source : _sources)
    {
      source->reload(_config.get());
    }
  }

public:
  Bus *bus(void) { return this; }

private:
  void post(std::unique_ptr<Log> &&msg) override;

public:
  SourceRegistry *sources(void) { return this; }

private:
  void attach(Source *source) override
  {
    source->reload(config());
    _sources.insert(source);
  }

  void detach(Source *source) override
  {
    _sources.erase(source);
  }

public:
  SinkRegistry *sinks(void) { return this; }

private:
  void append(std::unique_ptr<Sink> &&sink) override
  {
    _sinks.insert(std::move(sink));
  }

private:
  std::unique_ptr<Config> _config;
  std::set<Source *> _sources;
  std::set<std::unique_ptr<Sink>> _sinks;
};

} // namespace hermes

#endif // __HERMES_CONTEXT_H__
