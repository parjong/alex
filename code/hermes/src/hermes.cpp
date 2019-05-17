#include "hermes.h"

#include <cassert>

namespace hermes
{

Message::Text::Text(std::stringstream &ss)
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

} // namespace hermes

namespace hermes
{

MessageBuffer::MessageBuffer(MessageBus *bus) : _bus{bus}
{
  // DO NOTHING
}

MessageBuffer::~MessageBuffer()
{
  // To be safe, the method belows should be exception-free or asynchronous.
  auto msg = std::make_unique<Message>();

  msg->text(std::make_unique<Message::Text>(_ss));

  _bus->post(std::move(msg));
}

} // namespace hermes

namespace hermes
{

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

std::unique_ptr<MessageBuffer> Source::buffer(const Severity &) const
{
  // TODO Pass Severity
  return std::make_unique<MessageBuffer>(_ctx->bus());
}

} // namespace hermes
