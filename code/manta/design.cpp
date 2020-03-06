#if 0
Syntax syntax;

Mark m;

add_pattern(&syntax)
  .after("A")
  .after("B")
  .after("C")
  .after(any())
  .mark_as(&state_1)
;

auto e = make_engine(&syntax);

e[m] = [] (Trace *t) { ... };

// Q. How to handle syntax errors (w/ proper messages)
e.feed("A");
e.feed("B");
e.feed("C");

#endif

#if 0
Syntax syntax;

add_pattern(&m)
  .after("BEG")
  .enter_loop()
  .after(any())
  .reset_loop()
  .after("END")
  .leave_loop();
  .run(f)
;

// BEG 1 2 3 4 5 END [CALL F]
// BEG 1 2 3 END [CALL F] BEG 1 END [CALL F]
#endif

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>

struct Machine
{
  struct Context
  {
  };

  using Action = std::function<void (Machine::Context *)>;

  uint32_t current = 0;

  void feed(const std::string &s)
  {
    assert(actions.find(current) == actions.end());
  }

  std::map<uint32_t, Action> actions;
};

struct Any { };

struct State
{
  Machine *m;
  uint32_t num;

  State when(const std::string &s)
  {
    State ret;
    ret.m = m;
    ret.num = num;
    return ret;
  }

  State when(const Any &)
  {
    State ret;
    ret.m = m;
    ret.num = num;
    return ret;
  }

  void run(const Machine::Action &f)
  {
    m->actions[num] = f;
  }
};

State build(Machine *m)
{
  State s;

  s.m = m;
  s.num = 0;

  return s;
}

int main(int argc, char **argv)
{
  std::cout << "Hello" << std::endl;

  Machine m;

  auto s = build(&m)
    .when("SET")
    .when("MCELL")
  ;
#if 0
    .when(any())
    .when(any())
#endif

  s.run([] (Machine::Context *) {
    std::cout << "Hello" << std::endl;
  });

  m.feed("SET");
  m.feed("MCELL");
  m.feed("0");
  m.feed("1");

  return 0;
}
