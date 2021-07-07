#include <pepper/testing.hpp>
#include <pepper/cmdline.hpp>
#include <pepper/vector.hpp>
#include <pepper/exn.hpp>

#include <iostream>

COLLECTION(cmdline)
{
  class action : public pepper::cmdline::action::desc
  {
    public:
      virtual unsigned int perform(const pepper::cmdline::reader &r) 
      {
        std::cout << "Hello, World" << std::endl;
        return 0;
      }

    public:
      action() = default;
      virtual ~action() = default;
  };

  FACT(simple_usage_scenario)
  {
    // Create a command-line description
    pepper::cmdline::simple::desc desc;

    // Add a command-line option
    desc
      .option("--option")
      .action(std::shared_ptr<pepper::cmdline::action::desc>{new ::action});

    // Create a command-line parser
    pepper::cmdline::parser op{desc};

    // Create a command-line arguments
    pepper::vector::object<std::string> args;

    args.emplace("--option");

    // Create a command-line cursor
    auto cur = args.collection().cursor();

    // Parse the command-line via the accessor
    EXPECT_FALSE(op.parse(cur.object()));
  }
}
