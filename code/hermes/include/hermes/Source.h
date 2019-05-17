#ifndef __HERMES_SOURCE_H__
#define __HERMES_SOURCE_H__

#include "hermes/Severity.h"
#include "hermes/Log.h"
#include "hermes/Filter.h"

#include <memory>
#include <sstream>

namespace hermes
{

struct Bus
{
  virtual ~Bus() = default;

  /// Bus takes the ownership of posted messages
  virtual void post(std::unique_ptr<Log> &&msg) = 0;
};

/**
 * @brief Log Builder
 *
 * Q(parjong) Do we need a specialized builder for some sources?
 */
class Builder final
{
public:
  Builder();
  ~Builder();

public:
  void bus(Bus *b) { _bus = b; }

private:
  Bus *_bus = nullptr;

public:
  std::ostream &os(void) { return _ss; }

private:
  // Message
  std::stringstream _ss;

public:
  void severity(const Severity &s);

private:
  // Attributes
  std::unique_ptr<Severity> _severity = nullptr;
};

struct Context;
struct Config;

/**
 * @brief Minimal Source Implementation
 */
class Source
{
protected:
  Source();
  virtual ~Source();

protected:
  // Each derived "Source" SHOULD invoke activate/deactivate correctly
  void activate(Context *);
  void deactivate(void);

private:
  Context *_ctx = nullptr;

public:
  /**
   * @brief Return true if this source accepts logs with a given severity
   *
   * This method SHOULD BE optimized as apps invoke this method even when logging is disabled.
   */
  inline bool accept(const Severity &s) const { return _filter.accept(s); }

public:
  std::unique_ptr<Builder> builder(const Severity &) const;

public:
  /**
   * @brief Reload configuration
   *
   * WARNING
   *   Do NOT invoke this method explicitly. Only Context is allowed to access this method.
   *
   * Q(parjong) How to restrict the visibility?
   */
  void reload(const Config *config);

private:
  Filter _filter;
};

/**
 * @brief Source Registry
 *
 * The registered sources should outlive registry itself.
 *
 * Q(parjong) How to guarantee this if both Source and SourceRegistry are in global scope?
 * Q(parjong) Is this guarantee needed?
 */
struct SourceRegistry
{
  virtual ~SourceRegistry() = default;

  virtual void attach(Source *) = 0;
  virtual void detach(Source *) = 0;
};

} // namespace herems

#define HERMES_INFO(s) if ((s).accept(::hermes::info())) (s).builder(::hermes::info())->os()

#endif // __HERMES_SOURCE_H__
