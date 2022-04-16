#include "lib.h"

using ControllerPredicate = std::function<bool (const Controller &)>;
using ControllerAction = std::function<void (Controller &)>;

#include <map>
#include <stack>
#include <cassert>

class PredBuilder
{
public:
  using context_t = std::map<std::string, Tag *>;

public:
  PredBuilder(const context_t &context) : _context(context)
  {

  }

public:
  PredBuilder &add_string(const std::string &s);
  PredBuilder &add_symbol(char c);
  ControllerPredicate eof(void);

private:
  enum class Token { AND, OR, NOT };

private:
  void add_symbol(const Token &);

private:
  uint32_t precedence(const Token &t) const
  {
    switch (t)
    {
      case Token::AND:
        return 1;
      case Token::OR:
        return 1;
      case Token::NOT:
        return 0;
    };

    throw "not implemented, yet";
  }

  ControllerPredicate build(const Token &t)
  {
    switch (t)
    {
      case Token::NOT:
      {
        auto pred = _pstack.top(); _pstack.pop();

        return [pred] (const Controller &o)
        {
          return !pred(o);
        };
      }
      case Token::OR:
      {
        auto rhs = _pstack.top(); _pstack.pop();
        auto lhs = _pstack.top(); _pstack.pop();

        return [lhs, rhs] (const Controller &o)
        {
          return lhs(o) || rhs(o);
        };
      }
      case Token::AND:
      {
        auto rhs = _pstack.top(); _pstack.pop();
        auto lhs = _pstack.top(); _pstack.pop();

        return [lhs, rhs] (const Controller &o)
        {
          return lhs(o) && rhs(o);
        };
      }
    }

    throw "not implemented, yet";
  }

private:
  const context_t &_context;

  std::stack<ControllerPredicate> _pstack;
  std::stack<Token> _tstack;
};

PredBuilder &PredBuilder::add_string(const std::string &s)
{
  auto tag = _context.at(s);

  auto pred = [tag, s](const Controller &o)
  {
    return o.tags.find(tag) != o.tags.end();
  };

  _pstack.push(pred);

  return (*this);
}

void PredBuilder::add_symbol(const Token &curr)
{
  if (_tstack.empty())
  {
    _tstack.push(curr);
    return;
  }
    
  auto last = _tstack.top();

  // TODO precedence(last) == precedence(curr)
  if (precedence(last) <= precedence(curr))
  {
    _pstack.push(build(last));
    _tstack.push(curr);
  }
  else
  {
    _tstack.push(curr);
  }
}

PredBuilder &PredBuilder::add_symbol(char c)
{
  switch(c)
  {
    case '!':
      add_symbol(Token::NOT);
      break; 
    case '&':
      add_symbol(Token::AND);
      break;
    case '|':
      add_symbol(Token::OR);
      break;
  }
  return (*this);
}

ControllerPredicate PredBuilder::eof(void)
{
  while (!_tstack.empty())
  {
    auto last = _tstack.top();
    _pstack.push(build(last));
    _tstack.pop();
  }

  assert(_pstack.size() == 1);

  auto res = _pstack.top();
  _pstack.pop();
  return res;
}

struct ActionBuilder
{
  enum class ActionType
  {
    UNKNOWN,
    SET,
    UNSET
  };

  ActionType _type;
  ControllerAction _manip;

  ActionBuilder() : _type(ActionType::UNKNOWN)
  {
  };

  ActionBuilder &op_set()
  {
    _type = ActionType::SET;
    return (*this);
  }

  void add_string(const std::string &value)
  {
    long int number = std::strtol(value.c_str(), nullptr, 0);

    _manip = [number](Controller &o)
    {
      o.mask() |= number;
    };
  }

  ControllerAction eof(void)
  {
    return _manip;
  }
};


struct OwnContext : public Context
{
#define TAG(NAME) static Tag NAME;
#include "tag.lst"
#undef TAG
};

#define TAG(NAME) Tag OwnContext::NAME;
#include "tag.lst"
#undef TAG

static OwnContext context;

#define POINT_BEG(name) \
  static Point name(&context, [] (Controller *o)

#define POINT_END );

#define POINT_TAG(name) o->tags.insert(&OwnContext::name)

#define POINT_LOG(name, level) if (name.active(Level::level)) std::cout

void func_1(void)
{
  POINT_BEG(p)
  {
    POINT_TAG(A);
    POINT_TAG(B);
  }
  POINT_END;

  POINT_LOG(p, VERBOSE) << "Hello, World from " << __LINE__ << std::endl;
}

void func_2(void)
{
  POINT_BEG(p)
  {
    POINT_TAG(A);
  }
  POINT_END;

  POINT_LOG(p, VERBOSE) << "Hello, World from " << __LINE__ << std::endl;
}

template <typename... Args> struct multicast
{
  std::vector<std::function<void (Args...)>> _functions;

  void operator()(Args&&... args)
  {
    for (const auto &function : _functions)
    {
      function(std::forward<Args>(args)...);
    }
  }
};

template <typename... Args>
multicast<Args...> &operator<<(multicast<Args...> &args, const std::function<void (Args...)> &f)
{
  args._functions.emplace_back(f);
  return args;
}

struct Token
{
  virtual ~Token() = default;

  virtual bool is_valid(uint32_t offset, char c) = 0;
};

struct Lexer
{
  virtual ~Lexer() = default;

  virtual std::unique_ptr<Token> next(void) = 0;
};

int main(int argc, char **argv)
{
  PredBuilder::context_t pred_context;

  pred_context["A"] = &OwnContext::A;
  pred_context["B"] = &OwnContext::B;

  PredBuilder predicate_builder(pred_context);

  ActionBuilder action_builder;

  const std::string arg{ argv[1] };

  std::string buffer;

  enum class Mode { PREDICATE, ACTION };

  // START
  // PREDICATE
  // PREDICATE_VARIABLE
  // ACTION
  // ACTION_SYMBOL
  // ACTION_NUMBER
  Mode mode = Mode::PREDICATE;

  std::map<char, std::function<void (char)>> actions;

  auto delim_fn = [&] (char c)
  {
    if (!buffer.empty())
    {
      if (mode == Mode::PREDICATE)
      {
        predicate_builder.add_string(buffer);
      }
      else
      {
        // mode == Mode::ACTION
        action_builder.add_string(buffer);
      }
    }

    buffer.clear();
  };

  Rule r;

  auto alphanum_fn = [&buffer] (char c)
  {
    buffer.push_back(c);
  };

  // Process and(&), or(|), not(!)
  auto symbol_fn = [&] (char c)
  {
    delim_fn(c);
    predicate_builder.add_symbol(c);
  };

  // Rule termination
  auto terminal_fn = [&] (char c)
  {
    delim_fn(c);
    r.manip = action_builder.eof();
    context.rules.emplace_back(r);
    mode = Mode::PREDICATE;
  };

  std::set<char> alphanums;

  for (auto c = 'a'; c <= 'z'; ++c) { alphanums.insert(c); }
  for (auto c = 'A'; c <= 'Z'; ++c) { alphanums.insert(c); }
  for (auto c = '0'; c <= '9'; ++c) { alphanums.insert(c); }

  for (const auto &c : alphanums)
  {
    actions[c] = alphanum_fn;
  }

  actions['&'] = symbol_fn;
  actions['|'] = symbol_fn;
  actions['!'] = symbol_fn;

  actions[':'] = [&] (char c)
  {
    delim_fn(c);
    r.pred = predicate_builder.eof();
    mode = Mode::ACTION;
  };

  actions['='] = [&] (char c)
  {
    action_builder.op_set();
  };

  actions[','] = terminal_fn;
  actions[0] = terminal_fn;

  for (const auto c : arg)
  {
    const auto &fn = actions[c];
    fn(c);
  }
  {
    const auto &fn = actions[0];
    fn(0);
  }

  // Reload
  context.reload();

  func_1();
  func_2();

  return 0;
}
