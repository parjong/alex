#include "action.h"

#include <fstream>

class lower_observer : public lowering::observer
{
  private:
    std::ostream &_os;

  public:
    lower_observer(std::ostream &os) : _os(os)
    {
      // DO NOTHING
    }

    virtual ~lower_observer() = default;

  public:
    virtual void forward(const std::string &arg, const std::string &tok)
    {
      _os << "[LOWER] " << arg << " -> " << tok << std::endl;
    }
};

class parse_observer : public parsing::observer
{
  private:
    std::ostream &_os;

  public:
    parse_observer(std::ostream &os) : _os(os)
    {
      // DO NOTHING
    }

    virtual ~parse_observer() = default;

  public:
    virtual void tagged(const std::string &arg, const std::string &tag)
    {
      _os << "[" << tag << "] " << arg << std::endl;
    }
};

action::action(std::ostream &os, const std::string &path) : _os(os), _path{path}
{
  // DO NOTHING
}

void action::lower(lowering::context &ctx) const
{
  while (ctx.has_next())
  {
    le.run(ctx);
    ctx.pop();
  }
}

bool action::parse(parsing::context &ctx) const
{
  while (ctx.has_next())
  {
    if (!pe.run(ctx))
    {
      return false;
    }
  }

  return true;
}

bool action::act(const cana::proc::info &pi) const
{
  if (pi.image() != _path)
  {
    return false;
  }

  std::list<std::string> args;
  std::list<std::string> tokens;
  std::map<std::string, std::list<std::string>> tags;

  {
    auto fn = [&] (const std::string &arg)
    {
      _os << "[ARG] " << arg << std::endl;
      args.push_back(arg);
    };

    pi.arg().each(fn);
    args.pop_front();
  }

  // Lowering Phase
  {
    lower_observer    out(_os);
    lowering::context ctx(args, tokens, out);
    lower(ctx);
  }

  // Pasing Phase
  {
    parse_observer    out(_os);
    parsing::context  ctx(tokens, tags, out);
    parse(ctx);
  }

  // Running Phase
  {
    running::engine engine(tags, rcode);
    engine.run();
  }
  if (tokens.size() == 0)
  {
    _os << "DONE!" << std::endl;
  }
  else
  {
    _os << "[UNO] " << tokens.front() << std::endl;
  }

  return true;
}
