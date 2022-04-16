#include <pepper/testing.hpp>
#include <pepper/interop.hpp>

#include <iostream>
#include <sstream>

using namespace std::placeholders;

COLLECTION(interop)
{
  FACT(lua51_runtime_ctor_dtor)
  {
    pepper::interop::lua51::runtime rt;
  }

  FACT(lua51_empty_stack_at_beginning)
  {
    pepper::interop::lua51::runtime rt;

    EXPECT_EQ(rt.stack().size(), 0);
  }

  FACT(lua51_int_push_pop)
  {
    pepper::interop::lua51::runtime rt;

    rt.stack().push<int>(3);
    EXPECT_EQ(rt.stack().size(), 1);

    rt.stack().push<int>(4);
    EXPECT_EQ(rt.stack().size(), 2);

    EXPECT_EQ(rt.stack().pop<int>(), 4);
    EXPECT_EQ(rt.stack().size(), 1);

    EXPECT_EQ(rt.stack().pop<int>(), 3);
    EXPECT_EQ(rt.stack().size(), 0);
  }

  FACT(lua51_push_pop_string)
  {
    pepper::interop::lua51::runtime rt;

    rt.stack().push<std::string>("Hello?");
    EXPECT_EQ(rt.stack().size(), 1);
    EXPECT_EQ(rt.stack().pop<std::string>(), "Hello?");
    EXPECT_EQ(rt.stack().size(), 0);
  }

  FACT(lua51_heap_store_load)
  {
    pepper::interop::lua51::runtime rt;

    rt.stack().push<int>(4);
    rt.heap().store("x");
    EXPECT_EQ(rt.stack().size(), 0);

    rt.heap().load("x");
    int value = rt.stack().pop<int>();
    EXPECT_EQ(value, 4);
  }

  FACT(lua51_internal_call)
  {
    pepper::interop::lua51::runtime rt;
    pepper::interop::lua51::code::string::loader cl{"function succ (n) return n + 1 end"};

    rt.load(cl);
    rt.eval();

    rt.call("succ", 3);

    EXPECT_EQ(rt.stack().size(), 1);
    EXPECT_EQ(rt.stack().pop<int>(), 4);
  }

  int lua_external_succ(pepper::interop::lua51::stack::object &s)
  {
    int num = s.pop<int>();
    std::cout << "called with '" << num << "'!!" << std::endl;
    s.push<int>(num + 1);
    return 1;
  }

  FACT(lua51_external_call)
  {
    pepper::interop::lua51::runtime rt;

    rt.call(lua_external_succ, 3);

    EXPECT_EQ(rt.stack().size(), 1);
    EXPECT_EQ(rt.stack().pop<int>(), 4);
  }

  FACT(lua51_internal_call_multiret)
  {
    pepper::interop::lua51::runtime rt;
    pepper::interop::lua51::code::string::loader cl{"function dup (n) return n, n end"};

    rt.load(cl);
    rt.eval();

    rt.call("dup", 3);

    EXPECT_EQ(rt.stack().size(), 2);
    EXPECT_EQ(rt.stack().pop<int>(), 3);
    EXPECT_EQ(rt.stack().pop<int>(), 3);
  }

  int lua_external_dup(pepper::interop::lua51::stack::object &s)
  {
    int num = s.pop<int>();
    std::cout << "Let's duplicate '" << num << "'!!" << std::endl;
    s.push<int>(num);
    s.push<int>(num);
    return 2;
  }

  FACT(lua51_external_call_multret)
  {
    pepper::interop::lua51::runtime rt;

    rt.call(lua_external_dup, 3);
    EXPECT_EQ(rt.stack().size(), 2);

    EXPECT_EQ(rt.stack().pop<int>(), 3);
    EXPECT_EQ(rt.stack().pop<int>(), 3);
  }

  int lua_external_add(int lhs, pepper::interop::lua51::stack::object &s)
  {
    int rhs = s.pop<int>();
    std::cout << "Let's compute '" << lhs << " + " << rhs << "'!!" << std::endl;
    s.push<int>(lhs + rhs);
    return 1;
  }

  FACT(lua51_external_call_bind)
  {
    pepper::interop::lua51::runtime rt;

    rt.call(std::bind(lua_external_add, 3, _1), 4);

    EXPECT_EQ(rt.stack().size(), 1);
    EXPECT_EQ(rt.stack().pop<int>(), 7);
  }

  FACT(lua51_binding_push)
  {
    pepper::interop::lua51::runtime rt;

    rt.binder().push(std::bind(lua_external_add, 3, _1));
    EXPECT_EQ(rt.stack().size(), 1);

    rt.heap().store("f");
    EXPECT_EQ(rt.stack().size(), 0);

    rt.call("f", 4);
    EXPECT_EQ(rt.stack().size(), 1);
    EXPECT_EQ(rt.stack().pop<int>(), 7);
  }

  FACT(lua51_eval)
  {
    pepper::interop::lua51::runtime rt;
    pepper::interop::lua51::code::string::loader cl{"return 1 + 1;"};

    rt.load(cl);

    EXPECT_EQ(rt.eval(), 0);
    EXPECT_EQ(rt.stack().pop<int>(), 2);
  }

  FACT(lua51_stream_load)
  {
    pepper::interop::lua51::runtime rt;

    std::string code{"return 1 + 1;"};
    std::stringstream ss{code};

    pepper::interop::lua51::code::stream::loader cl{ss};

    rt.load(cl);

    EXPECT_EQ(rt.eval(), 0);
    EXPECT_EQ(rt.stack().pop<int>(), 2);
  }

}
