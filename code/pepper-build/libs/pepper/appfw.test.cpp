#include <pepper/testing.hpp>
#include <pepper/attr.hpp>
#include <pepper/appfw.hpp>
#include <pepper/vector.hpp>
#include <pepper/mem.hpp>

COLLECTION(appfwtests)
{
  class simple : public pepper::appfw::apps::basic::desc
  {
    private:
      pepper::attr::ref::accessor<std::string> _out;
      pepper::attr::ref::accessor<std::vector<std::string>> _args;

      const std::string _name;

    public:
      pepper::appfw::app::option::typed<int> num;

    public:
      virtual void enroll(pepper::appfw::app::option::set &os)
      {
        os.enroll( "--num", num );
      }

    public:
      virtual int main(pepper::appfw::apps::basic::service &srv)
      {
        // Output name
        _out = _name;

        // Output arguments
        auto output_fn = [&] (const std::string &arg)
        {
          _args().emplace_back(arg);
        };

        for (int num = 0; srv.cmdline().access(num).read(output_fn); ++num)
        {
          // DO NOTHING
        }

        // Return
        return 255;
      }

    public:
      simple(std::string &out, std::vector<std::string> &args, const std::string &name)
        : _out{ out }, _args{ args }, _name{ name }
      {
        // DO NOTHING
      }

    public:
      virtual ~simple() = default;
  };

  struct nested : public pepper::appfw::apps::nested::desc
  {
    nested() = default;
    virtual ~nested() = default;
  };

  FACT(usage)
  {
    // Construct an application
    std::string out;
    std::vector<std::string> args;

    auto app = pepper::mem::shared::make<::nested>();

    (*app)
      .command("simple")
      .set(pepper::mem::shared::make<::simple>(out, args, "hello"));

    // Construct an application host
    pepper::appfw::cli::host host{app};

    // Construct an argument list
    pepper::appfw::cli::args::vector::desc vec;

    vec.emplace("simple");

    // Run it!
    EXPECT_EQ(host.run(vec), 255);

    EXPECT_EQ(out, "hello");
    EXPECT_EQ(args.size(), vec.size() - 1);
  }

  FACT(simple_app)
  {
    // Construct an application
    std::string out;
    std::vector<std::string> args;

    auto app = pepper::mem::shared::make<::simple>(out, args, "hello");

    // Construct an application host
    pepper::appfw::cli::host host{app};

    // Construct an argument list
    pepper::appfw::cli::args::vector::desc vec;

    vec.emplace("--num");
    vec.emplace("3");

    // Run it!
    EXPECT_EQ(host.run(vec), 255);

    EXPECT_EQ(out, "hello");
    EXPECT_EQ(args.size(), 0);
    EXPECT_EQ((*app).num(), 3);
  }
}
