#include <pepper/appfw.hpp>
#include <pepper/mem.hpp>

#include <iostream>

struct show : public pepper::appfw::apps::basic::desc
{
  show()          = default;
  virtual ~show() = default;

  virtual int main(pepper::appfw::apps::basic::service &srv)
  {
    std::cout << "Hello, World!" << std::endl;

    auto show_fn = [&] (const std::string &arg)
    {
      std::cout << "  " << arg << std::endl;
    };

    for (int i = 0; srv.cmdline().access(i).read(show_fn); ++i)
    {
      // DO NOTHING
    }
    
    return 0;
  }
};

struct simple_runner : public pepper::appfw::apps::nested::desc
{
  simple_runner()          = default;
  virtual ~simple_runner() = default;
};

struct option_runner : public pepper::appfw::apps::nested::desc
{
  option_runner()          = default;
  virtual ~option_runner() = default;

  pepper::appfw::app::option::typed<int> num;

  virtual void enroll(pepper::appfw::app::option::set &os)
  {
    os.enroll("--num", num);
  }
};

int main(int argc, char **argv)
{
  auto opt = pepper::mem::shared::make<option_runner>();

  (*opt)
    .command("run")
    .set(pepper::mem::shared::make<show>());

  auto app = pepper::mem::shared::make<simple_runner>();

  (*app)
    .command("run")
    .set(pepper::mem::shared::make<show>());

  (*app)
    .command("opt")
    .set(opt);

  pepper::appfw::cli::host host{app};

  pepper::appfw::cli::args::block::desc args{argc, argv};

  return host.run(args);
}
