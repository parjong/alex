#include "hermes.h"

#include <cassert>

// TODO Create a file for each class

namespace hermes
{

//
// Message
//
Message::Message(std::stringstream &ss)
{
  while (!ss.eof())
  {
    assert(ss.good());

    std::string line;
    std::getline(ss, line);

    // Trim the last empty line (by std::endl)
    if (ss.eof() && line.empty())
    {
      break;
    }

    _lines.emplace_back(line);
  }
}

//
// Builder
//
Builder::Builder()
{
  // DO NOTHING
}

Builder::~Builder()
{
  // To be safe, the methods called below SHOULD NOT throw any exception.
  //
  // Q(parjong) How to make this safe?
  auto log = std::make_unique<Log>();

  log->msg(std::make_unique<Message>(_ss));
  log->severity(std::move(_severity));

  _bus->post(std::move(log));
}

void Builder::severity(const Severity &s)
{
  _severity = std::make_unique<Severity>(s);
}

//
// Filter
//
SeverityGroupSpecifier group(std::initializer_list<SeverityGroup> l)
{
  return SeverityGroupSpecifier(l);
}

SeverityGroupSpecifier all_groups(void)
{
  return group({FATAL, ERROR, WARN, INFO, VERBOSE});
}

FilterRule<FilterPolicy::AcceptAll> accept_all_rule(void)
{
  return FilterRule<FilterPolicy::AcceptAll>{};
}

FilterRule<FilterPolicy::DenyAll> deny_all_rule(void)
{
  return FilterRule<FilterPolicy::DenyAll>{};
}

//
// Source
//
Source::Source() : _ctx{nullptr}
{
  assert(_ctx == nullptr);
}

Source::~Source()
{
  assert(_ctx == nullptr);
}

void Source::activate(Context *ctx)
{
  assert(_ctx == nullptr);

  _ctx = ctx;
  _ctx->sources()->attach(this);

  assert(_ctx != nullptr);
}

void Source::deactivate(void)
{
  assert(_ctx != nullptr);

  _ctx->sources()->detach(this);
  _ctx = nullptr;

  assert(_ctx == nullptr);
}

std::unique_ptr<Builder> Source::builder(const Severity &s) const
{
  auto builder = std::make_unique<Builder>();

  builder->bus(_ctx->bus());
  builder->severity(s);

  return builder;
}

void Source::reload(const Config *config) { config->configure(this, _filter); }

//
// Context
//
void Context::post(std::unique_ptr<Log> &&log)
{
  assert(log->msg() != nullptr);
  assert(log->severity() != nullptr);

  // Take the ownership
  auto l = std::move(log);

  for (const auto &sink : _sinks)
  {
    sink->notify(l.get());
  }

  // TODO Stop immediately
  assert(log->severity()->group() != hermes::FATAL);
}

} // namespace hermes
