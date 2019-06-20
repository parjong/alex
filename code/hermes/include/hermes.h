#ifndef __HERMES_H__
#define __HERMES_H__

#include <memory>
#include <set>
#include <sstream>
#include <vector>
#include <array>

//
// Hermes is an **extensible** and **composable** logging framework
//
// NOTE "Hermes" heavily depends on RTTI to achieve its design goal.
//
// Goals
// - Always in
//
// Non-Goals
// - Always on
//

//
// include/
//   hermes/core/...
//   hermes/unit/BasicLogger.h
//   hermes/unit/ConsoleReporter.h
//
// Document:
//  - Specification & Rationale (i.e. Alternative Designs)
//  - Layout
//  - How to add a new Source
//  - How to add a new Sink
//  - How to add a new Config
//  - How to insert a logger
//

// POCO Notifications & Events (https://pocoproject.org/slides/090-NotificationsEvents.pdf)
// > Notifications are used if an observer does not know or does not
// > care about the source of an event.
//
// > Events are used if an observer does care about the source of an
// > event, or wants to receive events only from a particular source.
//
// Guava's Event Bus
//
// Otto (https://github.com/square/otto)
//
// RxJava (https://blog.kaush.co/2014/12/24/implementing-an-event-bus-with-rxjava-rxbus/)
//
// EventBus
//
// Google Log


//
// Core
//
namespace hermes
{

struct Severity final
{
public:
  // Category
  enum class Cat : uint16_t
  {
    FATAL = 0,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    VERBOSE = 4,
  };

private:
  Severity(Cat cat, uint16_t level) : _cat{cat}, _level{level}
  {
    // DO NOTHING
  }


public:
  const Cat &cat(void) const { return _cat; }
  // 0 is most significant
  // 65535 is least significant
  const uint16_t &level(void) const { return _level; }

private:
  Cat _cat;
  uint16_t _level;

public:
  static inline Severity info(void) { return Severity{Cat::INFO, 0}; }
};

} // namespace hermes

namespace hermes
{

class Message final
{
public:
  Message() = default;

public:
  class Text
  {
  public:
    Text(std::stringstream &ss);

  public:
    // Return the number of lines
    uint32_t lines(void) const { return _lines.size(); }
    // Return the content of a specific line
    const std::string &line(uint32_t n) const { return _lines.at(n); }

  private:
    std::vector<std::string> _lines;
  };

public:
  void text(std::unique_ptr<Text> &&text) { _text = std::move(text); }
  const Text *text(void) const { return _text.get(); }

private:
  std::unique_ptr<Text> _text;

public:
  // TODO Add "Timestamp" field
  // TODO Add "Source" field
  // TODO Add "Severity" field

  // TODO Support extensible "attribute"
};

struct MessageBus
{
  virtual ~MessageBus() = default;

  // MessageBus takes the ownership of posted messages
  virtual void post(std::unique_ptr<Message> &&msg) = 0;
};

// Temoprary Message Buffer
//
// Q. Is it necessary to define some interface and allows each source to implement their own version?
class MessageBuffer final
{
public:
  MessageBuffer(MessageBus *);
  ~MessageBuffer();

public:
  std::ostream &os(void) { return _ss; }

private:
  MessageBus *_bus;

  // Content
  std::stringstream _ss;
};

/**
 * Global Configuration
 */
struct Config
{
  virtual ~Config() = default;
};

/**
 * Rename "State" as "SourceConfiguration"?
 */
struct Context;

// Message Source
class Source
{
public:
  class BoundModifier final
  {
  public:
    BoundModifier(int32_t *ptr) : _ptr{ptr}
    {
      // DO NOTHING
    }

  public:
    inline void reject_all(void) { *_ptr = -1; }
    inline void accept_upto(uint16_t lv) { *_ptr = static_cast<int32_t>(lv); }
    inline void accept_all(void) { *_ptr = 65536; }

  private:
    int32_t *_ptr;
  };

  class BoundAccessor final
  {
  public:
    BoundAccessor(const int32_t *ptr) : _ptr{ptr}
    {
      // DO NOTHING
    }

  public:
    inline int32_t level(void) const { return *_ptr; }

  private:
    const int32_t *_ptr;
  };

  class Setting final
  {
  public:
    Setting()
    {
      // Reject all the messages by default
      reject_all();
    }

  public:
    void reject_all(void)
    {
      request(Severity::Cat::FATAL).reject_all();
      request(Severity::Cat::ERROR).reject_all();
      request(Severity::Cat::WARN).reject_all();
      request(Severity::Cat::INFO).reject_all();
      request(Severity::Cat::VERBOSE).reject_all();
    }

    void accept_all(void)
    {
      request(Severity::Cat::FATAL).accept_all();
      request(Severity::Cat::ERROR).accept_all();
      request(Severity::Cat::WARN).accept_all();
      request(Severity::Cat::INFO).accept_all();
      request(Severity::Cat::VERBOSE).accept_all();
    }

    inline BoundModifier request(const Severity::Cat &cat)
    {
      return _ulimits.data() + static_cast<uint32_t>(cat);
    }

    inline BoundAccessor limit(const Severity::Cat &cat) const
    {
      return _ulimits.data() + static_cast<uint32_t>(cat);
    }

  private:
    // Allowed level for each category
    //
    //  This source will accept all the messages whose level belongs to [0, ulimit)
    //  where ulimit corresdpons to "limit(cat).value()"
    //
    std::array<int32_t, 5> _ulimits;
  };

protected:
  Source();
  ~Source();

protected:
  // Each "Source" SHOULD invoke activate/deactivate correctly
  //
  // TODO Take "SourceRegistry" & "MessageBus"
  void activate(Context *);
  void deactivate(void);

protected:
  Setting &setting(void) { return _setting; }

public:
  // Check whether a message of a given severity is acceptable
  //
  // NOTE This routine is performance critical as app always invokes this routine 
  //      (even when logging is disabled).
  inline bool check(const Severity &s) const
  {
    return static_cast<int32_t>(s.level()) < _setting.limit(s.cat()).level();
  }

public:
  // Reload configuration!
  //   Context request reload upon configuration update
  //
  // Q. How to restrict the visibility? (Only Context is allowed to access this method)
  virtual void reload(const Config *) = 0;

public:
  std::unique_ptr<MessageBuffer> buffer(const Severity &) const;

private:
  Setting _setting;

  Context *_ctx;
};

} // namespace hereme

#define HERMES_INFO(s) \
  if ((s).check(::hermes::Severity::info())) (s).buffer(::hermes::Severity::info())->os()

namespace hermes
{

template <typename DerivedSource> struct SourceConfig
{
  virtual ~SourceConfig() = default;

  virtual void configure(const DerivedSource *, Source::Setting &) const = 0;
};

} // namespace hermes

namespace hermes
{

struct Sink
{
  virtual ~Sink() = default;

  virtual void notify(const Message *) = 0;
};

} // namespace

namespace hermes
{

struct SourceRegistry
{
  virtual ~SourceRegistry() = default;

  // NOTE Each Source should outlive SourceRegistry
  // Q. Is it possible to guarantee this when there is a global source registry?
  virtual void attach(Source *) = 0;
  virtual void detach(Source *) = 0;
};

struct SinkRegistry
{
  virtual ~SinkRegistry() = default;

  // NOTE SinkRegistry takes the ownership of all the appended Sink objects
  virtual void append(std::unique_ptr<Sink> &&) = 0;
  // TODO reset
};

class Context final : private MessageBus, private SourceRegistry, private SinkRegistry
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
  MessageBus *bus(void) { return this; }

private:
  void post(std::unique_ptr<Message> &&msg) override
  {
    // Validate message
    // assert(msg->text() != nullptr);

    // Take the ownership
    auto m = std::move(msg);

    for (const auto &sink : _sinks)
    {
      sink->notify(m.get());
    }

    // TODO Stop the process if the mssage is of "FATAL"
  }

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
  // TODO How to remove Sink? reset?
  void append(std::unique_ptr<Sink> &&sink) override
  {
    _sinks.insert(std::move(sink));
  }

private:
  std::unique_ptr<Config> _config;
  std::set<Source *> _sources;
  std::set<std::unique_ptr<Sink>> _sinks;
};

} // namespace

//
// Unit: Logger
//
namespace hermes
{

// Each extension needs to define these interfaces

} // namespace hermes

//
// Basic Logger
//
// "BasicLogger" is a very simple logger implementation that allows users to turn it on/off, but
// supports nothing else
//
namespace hermes
{

struct BasicLogger final : public Source
{
public:
  BasicLogger(Context *ctx) { activate(ctx); }
  ~BasicLogger() { deactivate(); }

public:
  void reload(const Config *config) override
  {
    // Let's check whether the current configuration is compatible with the current source
    auto logger_config = dynamic_cast<const SourceConfig<BasicLogger> *>(config);

    if (logger_config)
    {
      logger_config->configure(this, setting());
    }
    else
    {
      // Turn off by default
      setting().reject_all();
    }
  }
};

} // namespace hermes

//
// Reusable Sink Implementations
//
#include <iostream>

namespace hermes
{

// NOTE This code is not thread-safe
struct ConsoleReporter final : public Sink
{
  void notify(const Message *m) override
  {
    std::cout << m->text()->lines() << std::endl;
    for (uint32_t n = 0; n < m->text()->lines(); ++n)
    {
      std::cout << "  " << m->text()->line(n) << std::endl;
    }
  }
};

} // namespace hermes

#endif // __HERMES_H__

#if 0

How to configure each source?

Candidate 1: Configure when a user sends explicit notification

In this design, each user should invoke some "activate" method in "Context".

#endif
